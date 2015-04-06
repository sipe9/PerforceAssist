
#include "P4Task.hpp"

#include "Commands/P4Command.hpp"

#if defined(_WINDOWS)
#include <windows.h>
#undef SetPort
#else
#error Not implemented
#endif

#include <algorithm>

namespace VersionControl
{
	P4Task::P4Task() :
		m_isConnected(false),
		m_needsConnectionRefresh(false),
		m_client(),
		m_spec()
	{
	}

	P4Task::~P4Task()
	{
		disconnect();
	}

	void P4Task::setP4Port(const std::string &port)
	{
		m_client.SetPort(port.c_str());
		m_portConfig = port;
		m_needsConnectionRefresh = true;
	}

	std::string P4Task::getP4Port()
	{
		return m_portConfig.empty() ? std::string("perforce:1666") : m_portConfig;
	}

	void P4Task::setP4User(const std::string &user)
	{
		m_client.SetUser(user.c_str());
		m_userConfig = user;
		m_needsConnectionRefresh = true;
	}

	std::string P4Task::getP4User()
	{
		return m_client.GetUser().Text();
	}

	void P4Task::setP4Client(const std::string &client)
	{
		m_client.SetClient(client.c_str());
		m_clientConfig = client;
		m_needsConnectionRefresh = true;
	}

	std::string P4Task::getP4Client()
	{
		return m_client.GetClient().Text();
	}

	void P4Task::setP4Password(const std::string &password)
	{
		if(password.empty())
		{
			m_client.SetIgnorePassword();
		}
		else
		{
			m_client.SetPassword(password.c_str());
		}
		
		m_passwordConfig = password;
		m_needsConnectionRefresh = true;
	}

	const std::string P4Task::getP4Password() const
	{
		return m_passwordConfig;
	}

	void P4Task::setP4Host(const std::string &host)
	{
		m_client.SetHost(host.c_str());
		m_hostConfig = host;
		m_needsConnectionRefresh = true;
	}

	std::string P4Task::getP4Host()
	{
		return m_client.GetHost().Text();
	}

	void P4Task::setP4Root(const std::string &root)
	{
		m_root = root;
	}

	const std::string P4Task::getP4Root() const
	{
		return m_root;
	}

	bool P4Task::isConnected()
	{
		return (m_isConnected && !m_needsConnectionRefresh && !m_client.Dropped());
	}

	bool P4Task::disconnect()
	{
		Error err;

		m_client.Final(&err);
		m_isConnected = false;
		m_needsConnectionRefresh = false;

		if(err.Test())
		{
			printf("Failed to disconnect!\n");
			return false;
		}

		return true;
	}

	bool P4Task::runCommand(P4Command *cmd, const CommandArgs &args)
	{
		return cmd->Run(*this, args);
	}

	bool P4Task::connect(const std::string &user, const std::string &password, const std::string &host)
	{
		if(isConnected())
		{
			return true;
		}

		setP4User(user);
		setP4Password(password);
		setP4Host(host);
		
		m_client.SetProg("VersionControl");
		m_client.SetVersion("1.0");
		m_client.SetVar("enableStreams");
		m_client.SetProtocol("enableStreams", "");

		Error err;
		m_client.Init(&err);

		if(err.Test())
		{
			printf("Failed to connect %s!\n", host.c_str());
			return false;
		}		

		m_isConnected = true;
		m_needsConnectionRefresh = false;

		return true;
	}

	bool P4Task::runP4Command(const std::string &cmd, const CommandArgs &args, P4Command *client)
	{
		if(cmd.empty())
		{
			printf("Invalid P4 command!\n");
			return false;
		}

		if(m_needsConnectionRefresh)
		{
			// todo: refresh connection!
		}

		std::vector<char*> argBuffer;
		std::vector<std::string> localCopy;

		if(args.size() > 0)
		{				
			// Local copy
			for(int i = 0; i < static_cast<int>(args.size()); i++)
			{
				localCopy.push_back(std::string(args[i]));
			}

			// Push to buffer
			for(auto &t : localCopy)
			{
				argBuffer.push_back(&t[0]);
			}
		}

		// End with null
		argBuffer.push_back(0);

		// Set argument
		m_client.SetArgv(argBuffer.size() - 1, &argBuffer[0]);

		// Run command
		m_client.Run(cmd.c_str(), client);

		return true;
	}
}


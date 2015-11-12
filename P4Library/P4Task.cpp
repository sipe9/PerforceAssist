#include "P4Task.hpp"

#include "Commands/P4Command.hpp"
#include "Commands/P4LoginCommand.hpp"

#if defined(_WINDOWS)
#include <windows.h>
#undef SetPort
#else
#error Not implemented
#endif

#include <algorithm>

static char* g_programName = "VersionControl";
static int g_programVersionMajor = 0;
static int g_programVersionMinor = 5;
static int g_programVersionPatch = 0;

namespace VersionControl
{
    P4Task::P4Task() :
        m_isConnected(false),
		m_loginRequired(false),
        m_client()
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
    }

    std::string P4Task::getP4Port()
    {
        return m_portConfig.empty() ? std::string("localhost:1666") : m_portConfig;
    }

    void P4Task::setP4User(const std::string &user)
    {
        m_client.SetUser(user.c_str());
        m_userConfig = user;
    }

    std::string P4Task::getP4User()
    {
        return m_client.GetUser().Text();
    }

    void P4Task::setP4Client(const std::string &client)
    {
        m_client.SetClient(client.c_str());
        m_clientConfig = client;
    }

    std::string P4Task::getP4Client()
    {
        return m_client.GetClient().Text();
    }

    void P4Task::setP4Host(const std::string &host)
    {
        m_client.SetHost(host.c_str());
        m_hostConfig = host;
    }

    std::string P4Task::getP4Host()
    {
        return m_client.GetHost().Text();
    }

    bool P4Task::isConnected()
    {
        return (m_isConnected && !m_client.Dropped());
    }

    bool P4Task::disconnect()
    {
        Error err;

        m_client.Final(&err);
        m_isConnected = false;

        if(err.Test())
        {
            printf("Failed to disconnect!\n");
            return false;
        }

        return true;
    }

    bool P4Task::runCommand(P4Command &cmd)
    {
		if (!isConnected())
		{
			return false;
		}

        return cmd.Run(*this);
    }

	P4TaskConnectResult P4Task::connect(const std::string &user, const std::string &password)
    {
		m_passwordConfig = password;
		m_loginRequired = false;

        setP4User(user);

        m_client.SetProg(g_programName);

        std::string progVersion =
            std::to_string(g_programVersionMajor) + "." +
            std::to_string(g_programVersionMinor) + "." +
            std::to_string(g_programVersionPatch);

        m_client.SetVersion(progVersion.c_str());
        m_client.SetVar("enableStreams");
        m_client.SetProtocol("enableStreams", "");

        Error err;
        m_client.Init(&err);
		m_client.SetUi(this);

		if (err.Test() || m_client.Dropped())
        {
            printf("Failed to connect %s!\n", m_portConfig.c_str());
			return P4TaskConnectResult::Failed;
        }

		m_isConnected = true;

		P4LoginCommand login(password);
		login.Run(*this);

		/*if (login.isLoginRequired())
		{
			disconnect();
			return P4TaskConnectResult::LoginRequired;
		}
		else*/
		{
			return P4TaskConnectResult::Successful;
		}
    }

	bool P4Task::runP4Command(const std::string &cmd, const CommandArgs &args, ClientUser *client)
    {
		if (!isConnected())
			return false;

        if(cmd.empty())
        {
            printf("Invalid P4 command!\n");
            return false;
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
        m_client.SetArgv(static_cast<int>(argBuffer.size()) - 1, &argBuffer[0]);

        // Run command
        m_client.Run(cmd.c_str(), client);

        return true;
    }
}
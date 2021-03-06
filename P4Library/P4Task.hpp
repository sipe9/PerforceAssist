#pragma once

#include "Commands/P4Command.hpp"

#include "p4/clientapi.h"

#include <string>

namespace VersionControl
{
	enum P4TaskConnectResult
	{
		Successful = 0,
		Failed,
		LoginRequired,
	};

	class P4Task : public ClientUser
    {
    public:

        P4Task();
        ~P4Task();

		P4TaskConnectResult	connect(const std::string &user, const std::string &password);
        bool				disconnect();

        bool				isConnected();

        bool				runCommand(P4Command &cmd);

		bool				runP4Command(const std::string &cmd, const CommandArgs &args, ClientUser *client);

        std::string			getP4Port();
        std::string			getP4User();
        std::string			getP4Client();
        const std::string	getP4Password() const;
        std::string			getP4Host();
        const std::string	getP4Root() const;

        void				setP4Port(const std::string &port);
        void				setP4User(const std::string &user);
        void				setP4Client(const std::string &client);
        void				setP4Password(const std::string &password);
        void				setP4Host(const std::string &host);
        void				setP4Root(const std::string &root);

	private:

        bool				m_isConnected;
		bool				m_loginRequired;

        ClientApi			m_client;

        std::string			m_portConfig;
        std::string			m_userConfig;
        std::string			m_clientConfig;
        std::string			m_hostConfig;
        std::string			m_passwordConfig;
        std::string			m_commandOutput;
    };
}
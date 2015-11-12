#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Client.hpp"

#include <unordered_map>

namespace VersionControl
{
    class P4ClientsCommand : public P4Command
    {
    public:

		P4ClientsCommand(const std::string &username);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

		std::vector<P4ClientInfo>	GetClients() { return m_clients; }

    private:

		std::vector<P4ClientInfo>	m_clients;

		std::string					m_username;
    };
}
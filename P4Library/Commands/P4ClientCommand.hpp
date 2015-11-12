#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Client.hpp"

#include <unordered_map>

namespace VersionControl
{
    class P4ClientCommand : public P4Command
    {
    public:

		P4ClientCommand(const std::string &client, bool checkExistance = false);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const P4ClientData &GetClientData() const { return m_clientResult; }

    private:

        std::string		m_client;
		bool			m_checkExistance;
        P4ClientData	m_clientResult;
    };
}
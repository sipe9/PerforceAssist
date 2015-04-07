#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Client.hpp"

#include <unordered_map>

namespace VersionControl
{
    class P4ClientUpdateCommand : public P4Command
    {
    public:

        P4ClientUpdateCommand(const P4ClientData &clientData);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        virtual void InputData(StrBuf *strbuf, Error *e);

    private:

        static std::string CreateClientInputBuffer(const P4ClientData &clientData);

    private:

        bool			m_clientUpdated;

        P4ClientData	m_clientData;
    };
}
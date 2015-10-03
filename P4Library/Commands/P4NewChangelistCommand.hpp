#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    class P4NewChangelistCommand : public P4Command
    {
    public:

        P4NewChangelistCommand(const std::string &client, const std::string &user, const std::string &desc);

        virtual bool Run(P4Task &task);

        virtual void InputData(StrBuf *strbuf, Error *e);

        void OutputInfo(char level, const char *data);

		const std::string		GetChangeListNumber() const { return m_changelist; }

    private:

        std::string CreateInputBuffer(const std::string &client, const std::string &user, const std::string &desc);

        std::string		m_changelist;
        std::string		m_workspaceName;
        std::string		m_user;
        std::string		m_description;
    };
}
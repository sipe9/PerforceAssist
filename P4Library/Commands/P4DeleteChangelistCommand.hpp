#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

namespace VersionControl
{
    class P4DeleteChangelistCommand : public P4Command
    {
    public:

        P4DeleteChangelistCommand(const std::string &changelist);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        bool isDeleted() { return m_isDeleted; }

    private:

        std::string		m_changelist;
        bool			m_isDeleted;
    };
}
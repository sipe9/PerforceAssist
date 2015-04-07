#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Change.hpp"

namespace VersionControl
{
    class P4ChangesCommand : public P4Command
    {
    public:

        P4ChangesCommand(const std::string &user);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::vector<P4ChangeData> &GetChanges() const { return m_changes; }

    private:

        std::string		m_user;

        std::vector<P4ChangeData> m_changes;
    };
}
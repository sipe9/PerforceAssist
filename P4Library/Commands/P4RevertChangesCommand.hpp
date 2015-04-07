#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    enum class P4RevertResult : int
    {
        Reverted = 0,
        Deleted,
        Unknown,
    };

    class P4RevertChangesCommand : public P4Command
    {
    public:

        P4RevertChangesCommand(bool onlyUnchanged);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4RevertResult> &GetFiles() const { return m_files; }

        P4RevertResult MessageToAddResult(const std::string &message);

        void SetChangelist(const std::string &changelist) { m_changelist = changelist; }

    private:

        std::string		m_changelist;
        bool			m_onlyUnchanged;

        std::unordered_map<std::string, P4RevertResult>	m_files;
    };
}
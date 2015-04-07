#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    enum class P4LockResult : int
    {
        Locked = 0,
        Failed,
        AlreadyLocked,
        Unknown
    };

    class P4LockCommand : public P4Command
    {
    public:

        P4LockCommand();

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4LockResult> &GetLockedFiles() const { return m_lockedFiles; }

    private:

        P4LockResult MessageToAddResult(const std::string &message);

        std::unordered_map<std::string, P4LockResult>	m_lockedFiles;
    };
}
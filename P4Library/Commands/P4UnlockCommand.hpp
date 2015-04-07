#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    enum class P4UnlockResult : int
    {
        Unlocked = 0,
        AlreadyUnlocked,
        Failed,
        Unknown
    };

    class P4UnlockCommand : public P4Command
    {
    public:

        P4UnlockCommand();

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4UnlockResult> &GetLockedFiles() const { return m_lockedFiles; }

    private:

        P4UnlockResult MessageToAddResult(const std::string &message);

        std::unordered_map<std::string, P4UnlockResult>	m_lockedFiles;
    };
}
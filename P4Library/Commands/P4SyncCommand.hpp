#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    enum class P4SyncResult : int
    {
        Updating = 0,
        Unknown,
    };

    class P4SyncCommand : public P4Command
    {
    public:

        P4SyncCommand(bool forceSync = false);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4SyncResult> &GetSyncedFiles() const { return m_syncedFiles; }

    private:

        P4SyncResult ParseResultFromMessage(const std::string &message);

        std::unordered_map<std::string, P4SyncResult>	m_syncedFiles;

        bool						m_forceSync;
    };
}
#include "P4SyncCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    static const char* g_SyncUpdating = "- updating";

    P4SyncCommand::P4SyncCommand(bool forceSync) :
        P4Command("sync"),
        m_forceSync(forceSync)
    {
    }

    bool P4SyncCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

        if(m_forceSync)
        {
            myArgs.emplace_back("-f");
        }

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        for(auto &path : m_paths)
        {
            myArgs.emplace_back(path);
        }

        return task.runP4Command("sync", myArgs, this);
    }

    void P4SyncCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            // Split from revision number and use depot location as map key
            if(StringUtil::Contains(line, "#"))
            {
                std::vector<std::string> split;
                StringUtil::Split(line, '#', split);
                if(split.size() > 0)
                {
                    m_syncedFiles[split[0]] = ParseResultFromMessage(line);
                }
            }
        }
    }

    P4SyncResult P4SyncCommand::ParseResultFromMessage(const std::string &message)
    {
        if(StringUtil::Contains(message, g_SyncUpdating))
        {
            return P4SyncResult::Updating;
        }
        else
        {
            printf("Failed to parse P4SyncResult from %s\n", message.c_str());
            return P4SyncResult::Unknown;
        }
    }
}
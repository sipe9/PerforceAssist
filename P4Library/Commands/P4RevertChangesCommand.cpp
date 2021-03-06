#include "P4RevertChangesCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{
    static const char* g_WasEditReverted = "was edit, reverted";
    static const char* g_WasAddAbandoned = "was add, abandoned";
    static const char* g_HasBeenMovedNotReverted = "has been moved, not reverted";
    static const char* g_WasDeletedReverted = "was delete, reverted";
    static const char* g_WasDeletedMovedReverted = "was move/delete, reverted";
    static const char* g_WasDeletedAddDeleted = "was move/add, deleted";
    static const char* g_WasEditUnlockedAndReverted = "was edit, unlocked and reverted";

    P4RevertChangesCommand::P4RevertChangesCommand(bool onlyUnchanged) :
        P4Command("revert"),
        m_changelist(""),
        m_onlyUnchanged(onlyUnchanged)
    {
    }

    bool P4RevertChangesCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

        if(m_onlyUnchanged)
        {
            myArgs.emplace_back("-a");
        }

        // Append changelist if available
        if(!m_changelist.empty())
        {
            myArgs.emplace_back("-c");
            myArgs.emplace_back(m_changelist);
        }

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        for(auto &path : m_paths)
        {
            myArgs.emplace_back(path);
        }

        return task.runP4Command("revert", myArgs, this);
    }

    void P4RevertChangesCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::string depotFilename = PathUtil::parsePathFromString(line);
            m_files[depotFilename] = MessageToAddResult(line);
        }
    }

    P4RevertResult P4RevertChangesCommand::MessageToAddResult(const std::string &message)
    {
        if(StringUtil::endsWith(message, g_WasEditReverted) ||
           StringUtil::endsWith(message, g_WasAddAbandoned) ||
           StringUtil::endsWith(message, g_WasDeletedReverted) ||
           StringUtil::endsWith(message, g_WasDeletedMovedReverted) ||
           StringUtil::endsWith(message, g_HasBeenMovedNotReverted) ||
           StringUtil::endsWith(message, g_WasEditUnlockedAndReverted))
        {
            return P4RevertResult::Reverted;
        }
        else if(StringUtil::endsWith(message, g_WasDeletedAddDeleted))
        {
            return P4RevertResult::Deleted;
        }
        else
        {
            printf("Failed to parse P4RevertResult from %s\n", message.c_str());
            return P4RevertResult::Unknown;
        }
    }
}
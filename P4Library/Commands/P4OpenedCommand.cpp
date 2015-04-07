#include "P4OpenedCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{
    static const char* g_openedForEdit = "- edit change";
    static const char* g_openedForDelete = "- delete change";
    static const char* g_openedForAdd = "- add change";
    static const char* g_openedForMoveDelete = "- move/delete change";
    static const char* g_openedForMoveAdd = "- move/add change";
    static const char* g_openedForEditDefault = "- edit default";
    static const char* g_openedForAddDefault = "- add default";

    P4OpenedCommand::P4OpenedCommand() :
        P4Command("opened")
    {
    }

    bool P4OpenedCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

        if(m_openedType == P4OpenedCommandType::Changelist && !m_changelist.empty())
        {
            myArgs.emplace_back("-c");
            myArgs.emplace_back(m_changelist);
        }
        else if(m_openedType == P4OpenedCommandType::Workspace && !m_workspace.empty())
        {
            myArgs.emplace_back("-C");
            myArgs.emplace_back(m_workspace);
        }
        else
        {
            printf("P4OpenCommand failed. SetChangelist() or SetWorkspace() must be called before running command!\n");
            return false;
        }

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        for(auto &path : m_paths)
        {
            myArgs.emplace_back(path);
        }

        return task.runP4Command("opened", myArgs, this);
    }

    void P4OpenedCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::string depotFilename = PathUtil::parseDepotPathFromString(line);
            m_openedFiles[depotFilename] = MessageToAddResult(line);
        }
    }

    P4OpenedResult P4OpenedCommand::MessageToAddResult(const std::string &message)
    {
        if(StringUtil::Contains(message, g_openedForEdit))
            return P4OpenedResult::OpenedForEdit;
        else if(StringUtil::Contains(message, g_openedForDelete))
            return P4OpenedResult::OpenedForDelete;
        else if(StringUtil::Contains(message, g_openedForAdd))
            return P4OpenedResult::OpenedForAdd;
        else if(StringUtil::Contains(message, g_openedForMoveDelete))
            return P4OpenedResult::OpenedForMoveDelete;
        else if(StringUtil::Contains(message, g_openedForMoveAdd))
            return P4OpenedResult::OpenedForMoveAdd;
        else if(StringUtil::Contains(message, g_openedForEditDefault))
            return P4OpenedResult::OpenedForEditDefualt;
        else if(StringUtil::Contains(message, g_openedForAddDefault))
            return P4OpenedResult::OpenedForAddDefualt;
        else
        {
            printf("Failed to parse P4OpenedResult from %s\n", message.c_str());
            return P4OpenedResult::Unknown;
        }
    }

    void P4OpenedCommand::SetChangelist(const std::string &changelist)
    {
        m_openedType = P4OpenedCommandType::Changelist;
        m_changelist = changelist;
    }

    void P4OpenedCommand::SetWorkspace(const std::string &workspace)
    {
        m_openedType = P4OpenedCommandType::Workspace;
        m_workspace = workspace;
    }
}
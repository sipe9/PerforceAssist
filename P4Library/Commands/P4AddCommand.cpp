#include "P4AddCommand.hpp"
#include "P4StatusCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{
    static const char* g_OpenedForAdd = "opened for add";
    static const char* g_CurrentlyOpenedForAdd = "currently opened for add";
    static const char* g_AlreadyOpenedForEdit = "can't add (already opened for edit)";
    static const char* g_WarningAddOfExistingFile = "warning: add of existing file";
    static const char* g_AddExistingFile = "can't add existing file";

    P4AddCommand::P4AddCommand(std::string changelist) :
        P4Command("add"),
        m_changelist(changelist)
    {
    }

    bool P4AddCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

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

        return task.runP4Command("add", myArgs, this);
    }

    void P4AddCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::string depotFilename = PathUtil::parseDepotPathFromString(line);
            m_files[depotFilename] = MessageToAddResult(line);
        }
    }

    P4AddResult P4AddCommand::MessageToAddResult(const std::string &message)
    {
        if(StringUtil::endsWith(message, g_CurrentlyOpenedForAdd))
            return P4AddResult::AlreadyOpenedForAdd;
        else if(StringUtil::endsWith(message, g_OpenedForAdd))
            return P4AddResult::OpenedForAdd;
        else if(StringUtil::endsWith(message, g_AlreadyOpenedForEdit))
            return P4AddResult::AlreadyOpenedForEdit;
        else if(StringUtil::endsWith(message, g_WarningAddOfExistingFile))
            return P4AddResult::AlreadyExists;
        else if(StringUtil::endsWith(message, g_AddExistingFile))
            return P4AddResult::AlreadyExists;
        else
        {
            printf("Failed to parse P4AddResult from %s\n", message.c_str());
            return P4AddResult::Unknown;
        }
    }
}
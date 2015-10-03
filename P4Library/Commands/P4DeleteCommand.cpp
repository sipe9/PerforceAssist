#include "P4DeleteCommand.hpp"
#include "P4StatusCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{
	static const char* g_OpenForDelete = "opened for delete";
    static const char* g_NotOnClient = "not on client.";
	static const char* g_CantDeleteOpenForAdd = "can't delete (already opened for add)";	

    P4DeleteCommand::P4DeleteCommand(std::string changelist) :
        P4Command("delete"),
        m_changelist(changelist)
    {
    }

    bool P4DeleteCommand::Run(P4Task &task)
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

        return task.runP4Command("delete", myArgs, this);
    }

    void P4DeleteCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
			printf("%s\n", line.c_str());
			
			bool isDrivePath = false;

			// Detect if file was missing and is drive path, not depot
			/*if (StringUtil::Contains(line, g_MissingFile))
			{
				if (line.length() > 1 && line[1] == ':')
				{
					isDrivePath = true;
				}
			}*/

			std::string depotFilename = PathUtil::parsePathFromString(line, isDrivePath);
            m_files[depotFilename] = MessageToAddResult(line);
        }
    }

    P4DeleteResult P4DeleteCommand::MessageToAddResult(const std::string &message)
    {
		if (StringUtil::endsWith(message, g_OpenForDelete))
			return P4DeleteResult::OpenedForDeleted;
        else if(StringUtil::endsWith(message, g_NotOnClient))
			return P4DeleteResult::NotInClient;
        else if(StringUtil::endsWith(message, g_CantDeleteOpenForAdd))
            return P4DeleteResult::CantDeleteOpenForAdd;
        else
        {
            printf("Failed to parse P4DeleteResult from %s\n", message.c_str());
            return P4DeleteResult::Unknown;
        }
    }
}
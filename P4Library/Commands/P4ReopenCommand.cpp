#include "P4ReopenCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{
	static const char* g_Reopened = "- reopened; change";

    P4ReopenCommand::P4ReopenCommand(const std::string &changelist) :
        P4Command("reopened"),
		m_changelist(changelist)
	{
	}

    bool P4ReopenCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;
		
         myArgs.emplace_back("-c");		

        if(m_changelist.empty())
        {  
            myArgs.emplace_back("Default");
        }
		else
		{
			myArgs.emplace_back(m_changelist);
		}

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        for(auto &path : m_paths)
        {
            myArgs.emplace_back(path);
        }

        return task.runP4Command("reopen", myArgs, this);
    }

    void P4ReopenCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::string depotFilename = PathUtil::parsePathFromString(line);
			m_reopenedFiles[depotFilename] = MessageToAddResult(line);
        }
    }

    P4ReopenResult P4ReopenCommand::MessageToAddResult(const std::string &message)
    {
        if(StringUtil::Contains(message, g_Reopened))
			return P4ReopenResult::Reopened;
        else
        {
            printf("Failed to parse P4ReopenResult from %s\n", message.c_str());
			return P4ReopenResult::Failed;
        }
    }
}
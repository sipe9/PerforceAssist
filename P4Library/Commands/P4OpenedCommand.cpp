
#include "P4OpenedCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	static const char* g_openedForEdit = "- edit change";
	static const char* g_openedForDelete = "- delete change";
	static const char* g_openedForAdd = "- add change";
	static const char* g_openedForMoveDelete = "- move/delete change";
	static const char* g_openedForMoveAdd = "- move/add change";

	P4OpenedCommand::P4OpenedCommand(std::string changelist, std::string workspace) : 
		P4Command("opened"),
		m_changelist(changelist),
		m_workspace(workspace)
	{
	}

	bool P4OpenedCommand::Run(P4Task &task, const CommandArgs &args)
	{
		CommandArgs myArgs;

		// Append changelist if available
		if(!m_changelist.empty())
		{
			myArgs.emplace_back("-c");
			myArgs.emplace_back(m_changelist);
		}
		// Append workspace
		else if(!m_workspace.empty())
		{
			myArgs.emplace_back("-C");
			myArgs.emplace_back(m_workspace);
		}

		// Append custom arguments
		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		// Append paths
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
			std::string depotFilename = StringUtil::parseDepotFilename(line);
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
		else
		{
			printf("Failed to parse P4OpenedResult from %s\n", message.c_str());
			return P4OpenedResult::Unknown;
		}
	}
}

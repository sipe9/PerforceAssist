
#include "P4EditCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	static const char* g_OpenedForEdit = "opened for edit";
	static const char* g_CantEditAlreadyOpenedForAdd = "can't edit (already opened for add)";
	static const char* g_AlreadyOpenedForEdit = "currently opened for edit";
	static const char* g_AlsoOpenedBy = "also opened by";	

	P4EditCommand::P4EditCommand(std::string changelist, bool reportOnlyEdited) : 
		P4Command("edit"),
		m_changelist(changelist),
		m_reportOnlyEdited(reportOnlyEdited)
	{
	}

	bool P4EditCommand::Run(P4Task &task, const CommandArgs &args)
	{
		CommandArgs myArgs;

		// Append changelist if available
		if(!m_changelist.empty())
		{
			myArgs.emplace_back("-c");
			myArgs.emplace_back(m_changelist);
		}

		// Append custom arguments
		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		// Append paths
		for(auto &path : m_paths)
		{
			myArgs.emplace_back(path);
		}		

		return task.runP4Command("edit", myArgs, this);
	}

	void P4EditCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while(std::getline(stream, line))
		{
			P4EditResult result = MessageToAddResult(line);

			if(m_reportOnlyEdited && result != P4EditResult::OpenedForEdit)
				continue;

			std::string depotFilename = PathUtil::parseDepotPathFromString(line);
			m_files[depotFilename] = result;
		}
	}

	P4EditResult P4EditCommand::MessageToAddResult(const std::string &message)
	{
		if(StringUtil::endsWith(message, g_AlreadyOpenedForEdit))
			return P4EditResult::AlreadyOpenedForEdit;
		else if(StringUtil::endsWith(message, g_OpenedForEdit))
			return P4EditResult::OpenedForEdit;
		else if(StringUtil::endsWith(message, g_CantEditAlreadyOpenedForAdd))
			return P4EditResult::AlreadyOpenedForAdd;
		else if (StringUtil::Contains(message, g_AlsoOpenedBy))
			return P4EditResult::AlsoOpenedBy;
		else
		{
			printf("Failed to parse P4EditResult from %s\n", message.c_str());
			return P4EditResult::Unknown;
		}
	}
}

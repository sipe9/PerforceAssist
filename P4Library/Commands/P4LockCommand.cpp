
#include "P4LockCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	static const char* g_Locking = "- locking";
	static const char* g_AlreadyLocking = "- already locked";	
	static const char* g_notOpenedOnThisClient = "not opened on this client.";
	

	P4LockCommand::P4LockCommand() : 
		P4Command("lock")
	{
	}

	bool P4LockCommand::Run(P4Task &task, const CommandArgs &args)
	{
		CommandArgs myArgs;

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		for(auto &path : m_paths)
		{
			myArgs.emplace_back(path);
		}		

		return task.runP4Command("lock", myArgs, this);
	}

	void P4LockCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while(std::getline(stream, line))
		{
			std::string depotFilename = PathUtil::parseDepotPathFromString(line);
			m_lockedFiles[depotFilename] = MessageToAddResult(line);
		}
	}

	P4LockResult P4LockCommand::MessageToAddResult(const std::string &message)
	{
		if(StringUtil::Contains(message, g_Locking))
			return P4LockResult::Locked;
		else if(StringUtil::Contains(message, g_AlreadyLocking))
			return P4LockResult::AlreadyLocked;
		else if(StringUtil::Contains(message, g_notOpenedOnThisClient))
			return P4LockResult::Failed;
		else
		{
			printf("Failed to parse P4LockResult from %s\n", message.c_str());
			return P4LockResult::Unknown;
		}
	}
}

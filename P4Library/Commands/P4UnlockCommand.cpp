
#include "P4UnlockCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	static const char* g_Unlocked = "- unlocking";
	static const char* g_AlreadyUnlocked = "- already unlocked";	
	static const char* g_notOpenedOnThisClient = "not opened on this client.";	

	P4UnlockCommand::P4UnlockCommand() : 
		P4Command("unlock")
	{
	}

	bool P4UnlockCommand::Run(P4Task &task, const CommandArgs &args)
	{
		CommandArgs myArgs;

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		for(auto &path : m_paths)
		{
			myArgs.emplace_back(path);
		}		

		return task.runP4Command("unlock", myArgs, this);
	}

	void P4UnlockCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while(std::getline(stream, line))
		{
			std::string depotFilename = PathUtil::parseDepotPathFromString(line);
			m_lockedFiles[depotFilename] = MessageToAddResult(line);
		}
	}

	P4UnlockResult P4UnlockCommand::MessageToAddResult(const std::string &message)
	{
		if(StringUtil::endsWith(message, g_Unlocked))
			return P4UnlockResult::Unlocked;
		else if(StringUtil::Contains(message, g_AlreadyUnlocked))
			return P4UnlockResult::AlreadyUnlocked;
		/*else if(StringUtil::Contains(message, g_notOpenedOnThisClient))
			return P4UnlockResult::Failed;*/
		else
		{
			printf("Failed to parse P4UnlockResult from %s\n", message.c_str());
			return P4UnlockResult::Unknown;
		}
	}
}

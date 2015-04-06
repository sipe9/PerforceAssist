
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
	struct P4PendingChangelistResult
	{
		std::string changelist;
		std::string creationtime;
		std::string user;
		std::string description;
		std::string status;
	};

	class P4PendingChangelistCommand : public P4Command
	{

	public:		

		P4PendingChangelistCommand(const std::string &user);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);		

	private:
		
		std::string		m_user;

		std::vector<P4PendingChangelistResult> m_pendingChangelists;
	};
}
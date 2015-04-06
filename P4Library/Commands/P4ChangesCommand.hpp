
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
	struct P4ChangesResult
	{
		std::string changelist;
		std::string creationtime;
		std::string user;
		std::string description;
		std::string status;
	};

	class P4ChangesCommand : public P4Command
	{

	public:		

		P4ChangesCommand(const std::string &user);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);		

		const std::vector<P4ChangesResult> &GetChanges() const { return m_changes; }

	private:
		
		std::string		m_user;

		std::vector<P4ChangesResult> m_changes;
	};
}
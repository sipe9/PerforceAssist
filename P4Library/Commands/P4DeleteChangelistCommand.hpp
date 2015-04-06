
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

namespace VersionControl
{
	class P4DeleteChangelistCommand : public P4Command
	{

	public:		

		P4DeleteChangelistCommand(const std::string &changelist);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);		

		bool isDeleted() { m_isDeleted; }

	private:
		
		std::string		m_changelist;
		bool			m_isDeleted;
	};
}
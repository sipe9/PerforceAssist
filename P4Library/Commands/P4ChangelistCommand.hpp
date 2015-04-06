
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Change.hpp"

namespace VersionControl
{
	class P4ChangelistCommand : public P4Command
	{

	public:		

		P4ChangelistCommand(const std::string &changelist);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);		

		const P4ChangeData &GetChangeDate() const { return m_changeData; }

	private:
		
		std::string		m_changelist;

		P4ChangeData	m_changeData;
	};
}
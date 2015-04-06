
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Change.hpp"

namespace VersionControl
{
	class P4ChangeUpdateCommand : public P4Command
	{

	public:		

		P4ChangeUpdateCommand(const P4ChangeData &client);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		virtual void InputData(StrBuf *strbuf, Error *e);

		void OutputInfo(char level, const char *data);		

		bool isUpdated() { return m_isUpdated; }

	private:

		static std::string CreateInputBuffer(const P4ChangeData &data);

	private:
		
		bool			m_isUpdated;

		P4ChangeData	m_changeData;
	};
}
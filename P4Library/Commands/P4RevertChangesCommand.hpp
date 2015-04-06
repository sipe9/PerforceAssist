
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
	enum class P4RevertResult : int
	{
		Reverted = 0,
		Deleted,
		Unknown,
	};

	class P4RevertChangesCommand : public P4Command
	{

	public:		

		P4RevertChangesCommand(std::string changelist, bool onlyUnchanged);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);

		const std::unordered_map<std::string, P4RevertResult> &GetFiles() const { return m_files; }

		P4RevertResult MessageToAddResult(const std::string &message);
		
	private:

		std::string		m_changelist;
		bool			m_onlyUnchanged;

		bool			m_reportOnlyReverted;

		std::unordered_map<std::string, P4RevertResult>	m_files;	
	};
}
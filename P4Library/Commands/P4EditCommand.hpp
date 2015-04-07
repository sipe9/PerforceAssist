
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
	enum class P4EditResult : int
	{
		OpenedForEdit = 0,
		AlreadyOpenedForAdd,
		AlreadyOpenedForEdit,
		AlsoOpenedBy,
		Unknown,
	};

	class P4EditCommand : public P4Command
	{

	public:		

		P4EditCommand(std::string changelist = "");

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);

		const std::unordered_map<std::string, P4EditResult> &GetFiles() const { return m_files; }

		P4EditResult MessageToAddResult(const std::string &message);
		
	private:

		std::string		m_changelist;

		std::unordered_map<std::string, P4EditResult>	m_files;	
	};
}
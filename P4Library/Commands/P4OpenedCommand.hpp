
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
	enum class P4OpenedResult : int
	{
		OpenedForEdit = 0,
		OpenedForDelete,
		OpenedForAdd,
		OpenedForMoveDelete,
		OpenedForMoveAdd,
		Unknown
	};

	class P4OpenedCommand : public P4Command
	{

	public:		

		P4OpenedCommand(std::string changelist, std::string workspace);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);

		const std::unordered_map<std::string, P4OpenedResult> &GetOpenedFiles() const { return m_openedFiles; }

	private:

		P4OpenedResult MessageToAddResult(const std::string &message);

		std::string		m_changelist;
		std::string		m_workspace;

		std::unordered_map<std::string, P4OpenedResult>	m_openedFiles;
	};
}

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
		OpenedForEditDefualt,
		OpenedForAddDefualt,
		Unknown
	};

	enum class P4OpenedCommandType : int
	{
		Changelist = 0,
		Workspace,
	};

	class P4OpenedCommand : public P4Command
	{

	public:		

		P4OpenedCommand();

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);

		const std::unordered_map<std::string, P4OpenedResult> &GetOpenedFiles() const { return m_openedFiles; }

		void SetChangelist(const std::string &changelist);
		void SetWorkspace(const std::string &workspace);

	private:

		P4OpenedResult MessageToAddResult(const std::string &message);

		std::string		m_changelist;
		std::string		m_workspace;

		P4OpenedCommandType m_openedType;

		std::unordered_map<std::string, P4OpenedResult>	m_openedFiles;
	};
}
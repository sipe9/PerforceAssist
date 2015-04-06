
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Depot.hpp"

#include <unordered_map>

namespace VersionControl
{
	class P4DepotCommand : public P4Command
	{

	public:		

		P4DepotCommand(const std::string &depotName);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);		

		const P4DepotData &GetDepotData() const { return m_depotData; }

	private:
		
		std::string		m_depotName;

		P4DepotData		m_depotData;
	};
}
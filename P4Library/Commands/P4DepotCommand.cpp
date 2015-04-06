
#include "P4DepotCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	static const char* g_Depot = "Depot:";
	static const char* g_Owner = "Owner:";
	static const char* g_Date = "Date:";
	static const char* g_Description = "Description:";
	static const char* g_Type = "Type:";
	static const char* g_Map = "Map:";	

	P4DepotCommand::P4DepotCommand(const std::string &depotName) : 
		P4Command("depot"),
		m_depotName(depotName)
	{
	}

	bool P4DepotCommand::Run(P4Task &task, const CommandArgs &args)
	{	
		if(m_depotName.empty())
		{
			printf("Failed to run P4DepotCommand, depot name is empty!\n");
			return false;
		}

		CommandArgs myArgs;
		myArgs.emplace_back("-o");
		myArgs.emplace_back(m_depotName);

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));
		return task.runP4Command("depot", myArgs, this);
	}

	void P4DepotCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;

		std::vector<std::string> lines;

		while(std::getline(stream, line))
		{
			lines.emplace_back(line);
		}

		for(unsigned i = 0; i < lines.size(); i++)
		{
			if (StringUtil::startsWithAndAssign(lines[i], g_Depot, m_depotData.depot, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Owner, m_depotData.owner, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Date, m_depotData.date, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Type, m_depotData.type, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Map, m_depotData.map, true)) continue;

			if(StringUtil::startsWith(lines[i], g_Description))
			{
				// Step to next line
				i++;

				do
				{
					std::string descLine = lines[i];
					descLine = StringUtil::TrimStart(descLine, ' ');
					descLine = StringUtil::TrimStart(descLine, '\t');

					m_depotData.description.emplace_back(descLine);

					i++;

				} while (i < lines.size() && StringUtil::startsWith(lines[i], "\t"));				

				continue;
			}
		}
	}
}

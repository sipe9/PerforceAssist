
#include "P4ChangelistCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	P4ChangelistCommand::P4ChangelistCommand(const std::string &changelist) : 
		P4Command("change"),
		m_changelist(changelist)
	{
	}

	bool P4ChangelistCommand::Run(P4Task &task, const CommandArgs &args)
	{
		if(m_changelist.empty())
		{
			printf("Failed to run P4ChangelistCommand, changelist number is empty!\n");
			return false;
		}

		CommandArgs myArgs;

		myArgs.emplace_back("-o");
		myArgs.emplace_back(m_changelist);

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		return task.runP4Command("change", myArgs, this);
	}

	void P4ChangelistCommand::OutputInfo(char level, const char *data)
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
			if (StringUtil::startsWithAndAssign(lines[i], "Change:", m_changeData.change, true))  continue;
			if (StringUtil::startsWithAndAssign(lines[i], "Date:", m_changeData.creationtime, true))  continue;
			if (StringUtil::startsWithAndAssign(lines[i], "Client:", m_changeData.client, true))  continue;
			if (StringUtil::startsWithAndAssign(lines[i], "User:", m_changeData.user, true))  continue;
			if (StringUtil::startsWithAndAssign(lines[i], "Status:", m_changeData.status, true))  continue;

			if (StringUtil::startsWith(lines[i], "Description:"))
			{
				// Step to next line
				i++;

				do
				{
					std::string descLine = lines[i];
					descLine = StringUtil::TrimStart(descLine, ' ');
					descLine = StringUtil::TrimStart(descLine, '\t');

					m_changeData.description.emplace_back(descLine);

					i++;

				} while (i < lines.size() && StringUtil::startsWith(lines[i], "\t"));				

				continue;
			}

			if (StringUtil::startsWith(lines[i], "Files:"))
			{
				// Step to next line
				i++;

				do
				{
					std::string filename = lines[i];
					filename = StringUtil::TrimStart(filename, ' ');
					filename = StringUtil::TrimStart(filename, '\t');

					filename = PathUtil::parseDepotPathFromString(filename);
					filename = StringUtil::Trim(filename, '\t');

					m_changeData.files.emplace_back(filename);

					i++;

				} while (i < lines.size() && StringUtil::startsWith(lines[i], "\t"));				

				continue;
			}
		}
	}
}

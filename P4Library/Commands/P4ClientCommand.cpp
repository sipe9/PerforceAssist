
#include "P4ClientCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	static const char* g_Client = "Client:";
	static const char* g_Update = "Update:";
	static const char* g_Access = "Access:";
	static const char* g_Owner = "Owner:";
	static const char* g_Host = "Host:";
	static const char* g_Description = "Description:";
	static const char* g_Root = "Root:";
	static const char* g_Options = "Options:";
	static const char* g_SubmitOptions = "SubmitOptions:";
	static const char* g_LineEnd = "LineEnd:";
	static const char* g_View = "View:";

	P4ClientCommand::P4ClientCommand(const std::string &client) : 
		P4Command("client"),
		m_client(client)
	{
	}

	bool P4ClientCommand::Run(P4Task &task, const CommandArgs &args)
	{
		CommandArgs myArgs;

		myArgs.emplace_back("-o");
		myArgs.emplace_back(m_client);

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		return task.runP4Command("client", myArgs, this);
	}

	void P4ClientCommand::OutputInfo(char level, const char *data)
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
			if (StringUtil::startsWithAndAssign(lines[i], g_Client, m_clientResult.client, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Update, m_clientResult.update, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Access, m_clientResult.access, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Owner, m_clientResult.owner, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Host, m_clientResult.host, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_Root, m_clientResult.root, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_SubmitOptions, m_clientResult.submitOptions, true)) continue;
			if (StringUtil::startsWithAndAssign(lines[i], g_LineEnd, m_clientResult.lineEnd, true)) continue;

			if (StringUtil::startsWith(lines[i], g_Options))
			{
				std::string tmp;
				StringUtil::startsWithAndAssign(lines[i], g_Options, tmp, true);
				StringUtil::Split(tmp, ' ', m_clientResult.options);
				continue;
			}

			if(StringUtil::startsWith(lines[i], g_Description))
			{
				// Step to next line
				i++;

				do
				{
					std::string descLine = lines[i];
					descLine = StringUtil::TrimStart(descLine, ' ');
					descLine = StringUtil::TrimStart(descLine, '\t');

					m_clientResult.descriptionLines.emplace_back(descLine);

					i++;

				} while (i < lines.size() && StringUtil::startsWith(lines[i], "\t"));				

				continue;
			}

			if(StringUtil::startsWith(lines[i], g_View))
			{
				// Step to next line
				i++;

				do
				{
					std::string view = lines[i];
					view = StringUtil::TrimStart(view, ' ');
					view = StringUtil::TrimStart(view, '\t');
					m_clientResult.view.emplace_back(view);

					i++;

				} while (i < lines.size() && StringUtil::startsWith(lines[i], "\t"));

				continue;
			}
		}
	}
}

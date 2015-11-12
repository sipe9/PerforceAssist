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

	P4ClientCommand::P4ClientCommand(const std::string &client, bool checkExistance) :
        P4Command("client"),
        m_client(client),
		m_checkExistance(checkExistance)
    {
    }

    bool P4ClientCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

        myArgs.emplace_back("-o");

		if (m_checkExistance)
		{
			myArgs.emplace_back("-t");
		}

        myArgs.emplace_back(m_client);

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

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
			std::string line = lines[i];

			if (line.empty())
				continue;

			// Early out if we get error from the output
			if (m_checkExistance)
			{
				if (StringUtil::startsWith("Client", line) &&
					StringUtil::Contains(m_client, line) &&
					StringUtil::Contains("unknown", line) &&
					StringUtil::Contains("command to create it", line))
				{
					m_clientResult.client = "";
					m_clientResult.owner = "";
					m_clientResult.root = "";
					m_clientResult.host = "";
					break;
				}
			}

			if (StringUtil::startsWithAndAssign(line, g_Client, m_clientResult.client, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_Update, m_clientResult.update, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_Access, m_clientResult.access, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_Owner, m_clientResult.owner, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_Host, m_clientResult.host, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_Root, m_clientResult.root, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_SubmitOptions, m_clientResult.submitOptions, true)) continue;
			if (StringUtil::startsWithAndAssign(line, g_LineEnd, m_clientResult.lineEnd, true)) continue;

			if (StringUtil::startsWith(line, g_Options))
            {
                std::string tmp;
                StringUtil::startsWithAndAssign(line, g_Options, tmp, true);
                StringUtil::Split(tmp, ' ', m_clientResult.options);
                continue;
            }

            if(StringUtil::startsWith(line, g_Description))
            {
                // Step to next line
                i++;

                do
                {
                    std::string descLine = line;
                    descLine = StringUtil::TrimStart(descLine, ' ');
                    descLine = StringUtil::TrimStart(descLine, '\t');

                    m_clientResult.description.emplace_back(descLine);

                    i++;
                } while(i < lines.size() && StringUtil::startsWith(line, "\t"));

                continue;
            }

            if(StringUtil::startsWith(line, g_View))
            {
                // Step to next line
                i++;

                do
                {
                    std::string view = line;
                    view = StringUtil::TrimStart(view, ' ');
                    view = StringUtil::TrimStart(view, '\t');
                    m_clientResult.view.emplace_back(view);

                    i++;
                } while(i < lines.size() && StringUtil::startsWith(line, "\t"));

                continue;
            }
        }
    }
}
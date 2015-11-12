#include "P4ClientsCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
	P4ClientsCommand::P4ClientsCommand(const std::string &username) :
        P4Command("client"),
		m_username(username)
    {
    }

    bool P4ClientsCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

		if (!m_username.empty())
		{
			myArgs.emplace_back("-u");
			myArgs.emplace_back(m_username);
		}        

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        return task.runP4Command("clients", myArgs, this);
    }

    void P4ClientsCommand::OutputInfo(char level, const char *data)
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
			std::vector<std::string> split;
			StringUtil::Split(lines[i], ' ', split);

			if (split.size() >= 4 && split[0] == "Client")
			{
				P4ClientInfo info;
				info.workspace = split[1];
				info.creationTime = split[2];
				info.type = split[3];
				info.clientRoot = split[4];

				m_clients.emplace_back(info);
			}
		}
    }
}
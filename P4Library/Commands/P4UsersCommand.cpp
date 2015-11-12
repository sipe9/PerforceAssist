#include "P4UsersCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    P4UsersCommand::P4UsersCommand() :
        P4Command("users")
    {
    }

    bool P4UsersCommand::Run(P4Task &task)
    {
        m_users.clear();

        CommandArgs myArgs;

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        for(auto &f : m_paths)
        {
            myArgs.emplace_back(f);
        }

        return task.runP4Command("users", myArgs, this);
    }

	void P4UsersCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while (std::getline(stream, line))
		{
			std::vector<std::string> split;
			StringUtil::Split(line, ' ', split);
			if (split.size() >= 3)
			{
				P4User user;
				user.username = split[0];
				user.email = split[1];
				user.name = split[2];

				if (StringUtil::startsWith(user.email, "<") && StringUtil::endsWith(user.email, ">"))
				{
					user.email = StringUtil::Substring(user.email, 1, static_cast<int>(user.email.length()) - 2);
				}

				if (StringUtil::startsWith(user.name, "(") && StringUtil::endsWith(user.name, ")"))
				{
					user.name = StringUtil::Substring(user.name, 1, static_cast<int>(user.name.length()) - 2);
				}

				m_users.emplace_back(user);
			}			
		}
	}
}
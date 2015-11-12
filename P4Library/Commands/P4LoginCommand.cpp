#include "P4LoginCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
	P4LoginCommand::P4LoginCommand(const std::string &password, bool globalTicket) :
        P4Command("login"),
		m_password(password),
		m_loginRequired(false),
		m_globalTicket(true)
    {
    }

    bool P4LoginCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;

		if (m_globalTicket)
		{
			myArgs.emplace_back("-a");
		}

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        return task.runP4Command("login", myArgs, this);
    }

	void P4LoginCommand::Prompt(const StrPtr &msg, StrBuf &rsp, int noEcho, Error *e)
	{
		StrBuf l;

		l.Set("Enter password: ");
		if (msg.SCompare(l) == 0)
		{
			if (m_password.empty())
			{
				m_loginRequired = true;
			}
			else
			{
				rsp.Append(m_password.c_str());
			}
		}
	}	
}
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"
#include "P4Change.hpp"

namespace VersionControl
{
    class P4LoginCommand : public P4Command
    {
    public:

		P4LoginCommand(const std::string &password, bool globalTicket = true);

        virtual bool Run(P4Task &task);

		bool isLoginRequired() { return m_loginRequired; }
		
	private:
	
		void Prompt(const StrPtr &msg, StrBuf &rsp, int noEcho, Error *e);

    private:

		std::string		m_password;

		bool			m_loginRequired;

		bool			m_globalTicket;
    };
}
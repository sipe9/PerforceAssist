#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>
#include <string>

namespace VersionControl
{
    struct P4User
    {
        std::string username;
        std::string email;
		std::string name;
    };

    class P4UsersCommand : public P4Command
    {
    public:

        P4UsersCommand();

        virtual bool Run(P4Task &task);

		void OutputInfo(char level, const char *data);

        const std::vector<P4User> &GetUsers() const { return m_users; }

    private:
	
        std::vector<P4User> m_users;
    };
}
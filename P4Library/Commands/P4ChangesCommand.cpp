#include "P4ChangesCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    static const char* g_Pending0 = "Change";
    static const char* g_Pending2 = "on";
    static const char* g_Pending4 = "by";

    P4ChangesCommand::P4ChangesCommand(const std::string &user) :
        P4Command("changes"),
        m_user(user)
    {
    }

    bool P4ChangesCommand::Run(P4Task &task)
    {
        m_changes.clear();

        CommandArgs myArgs;
        myArgs.emplace_back("-s");
        myArgs.emplace_back("pending");

        if(!m_user.empty())
        {
            myArgs.emplace_back("-u");
            myArgs.emplace_back(std::string(m_user));
        }

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        return task.runP4Command("changes", myArgs, this);
    }

    void P4ChangesCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::vector<std::string> split;
            StringUtil::Split(line, ' ', split);

            if(split.size() >= 8)
            {
                if(split[0] == g_Pending0 && StringUtil::IsPositiveNumber(split[1]) &&
                   split[2] == g_Pending2 &&
                   split[4] == g_Pending4)
                {
                    P4ChangeData result;
                    result.change = split[1];
                    result.creationtime = split[3];
                    result.user = split[5];
                    result.status = StringUtil::Trim(split[6], '*');

                    // Find 'description' from the string
                    std::string desc = line;
                    desc = StringUtil::SplitByFirstOf(desc, '\'', false);
                    desc = StringUtil::Trim(desc, '\'');

                    result.description.emplace_back(desc);

                    m_changes.emplace_back(result);
                }
            }
        }
    }
}
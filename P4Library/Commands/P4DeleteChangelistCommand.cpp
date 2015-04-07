#include "P4DeleteChangelistCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    P4DeleteChangelistCommand::P4DeleteChangelistCommand(const std::string &changelist) :
        P4Command("change"),
        m_changelist(changelist),
        m_isDeleted(false)
    {
    }

    bool P4DeleteChangelistCommand::Run(P4Task &task)
    {
        if(m_changelist.empty())
        {
            printf("Failed to delete changelist, changelist number is empty!\n");
            return false;
        }

        CommandArgs myArgs;
        myArgs.emplace_back("-d");
        myArgs.emplace_back(m_changelist);

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        return task.runP4Command("change", myArgs, this);
    }

    void P4DeleteChangelistCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::vector<std::string> split;
            StringUtil::Split(line, ' ', split);
            if(split.size() > 2 &&
               StringUtil::startsWith(split[0], "Change") &&
               StringUtil::startsWith(split[2], "deleted"))
            {
                m_isDeleted = true;
            }
            else
            {
                m_isDeleted = false;

                if(StringUtil::Contains(line, "open file(s)"))
                {
                    printf("Cannot delete changelist '%s' because it's not empty!\n", m_changelist.c_str());
                }
                else
                {
                    printf("Changelist '%s' delete has failed!\n", m_changelist.c_str());
                    printf("%s\n", line.c_str());
                }
            }
        }
    }
}
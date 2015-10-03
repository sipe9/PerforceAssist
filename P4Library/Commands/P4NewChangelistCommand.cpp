#include "P4NewChangelistCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    static const char* g_ChangePrefix = "Change";
    static const char* g_ChangeSuffix = "created.";

    P4NewChangelistCommand::P4NewChangelistCommand(const std::string &workspaceName, const std::string &user, const std::string &desc) :
        P4Command("change"),
        m_changelist(""),
		m_workspaceName(workspaceName),
        m_user(user),
        m_description(desc)
    {
    }

    bool P4NewChangelistCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;
        myArgs.emplace_back("-i");
        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));
        return task.runP4Command("change", myArgs, this);
    }

    void P4NewChangelistCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::vector<std::string> split;
            StringUtil::Split(line, ' ', split);
            if(split.size() == 3)
            {
                if(split[0] == g_ChangePrefix && StringUtil::IsPositiveNumber(split[1]) && split[2] == g_ChangeSuffix)
                {
                    m_changelist = split[1];
                }
                else
                {
                    printf("Failed to parse new change list number from %s, prefix (%s), number (%s) or suffix (%s) failed!\n",
						line.c_str(), split[0].c_str(), split[1].c_str(), split[2].c_str());
                }
            }
            else
            {
                printf("Failed to parse new change list number from %s\n", line.c_str());
            }
        }
    }

    void P4NewChangelistCommand::InputData(StrBuf *strbuf, Error *e)
    {
        std::string buf = CreateInputBuffer(m_workspaceName, m_user, m_description);
        strbuf->Set(buf.c_str());
    }

    std::string P4NewChangelistCommand::CreateInputBuffer(const std::string &workspaceName, const std::string &user, const std::string &desc)
    {
        std::string buf = "";
        buf += "Change:	new\n";
        buf += "Client:	" + workspaceName + "\n";
        buf += "User: " + user + "\n";
        buf += "Status: new\n";
        buf += "Description: " + desc + "\n";
        return std::move(buf);
    }
}
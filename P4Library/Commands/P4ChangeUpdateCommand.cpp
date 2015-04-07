#include "P4ChangeUpdateCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    P4ChangeUpdateCommand::P4ChangeUpdateCommand(const P4ChangeData &data) :
        P4Command("change"),
        m_changeData(data),
        m_isUpdated(false)
    {
    }

    bool P4ChangeUpdateCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;
        myArgs.emplace_back("-i");

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        return task.runP4Command("change", myArgs, this);
    }

    void P4ChangeUpdateCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;
        while(std::getline(stream, line))
        {
            std::vector<std::string> split;
            StringUtil::Split(line, ' ', split);

            if(split.size() > 2 &&
               split[0] == "Change" &&
               StringUtil::startsWith(split[2], "updated"))
            {
                m_isUpdated = true;
            }
            else
            {
                m_isUpdated = false;
                printf("Warning, change list update might not have been updated successfully! %s\n", line.c_str());
            }
        }
    }

    void P4ChangeUpdateCommand::InputData(StrBuf *strbuf, Error *e)
    {
        std::string buf = CreateInputBuffer(m_changeData);
        strbuf->Set(buf.c_str());
    }

    std::string P4ChangeUpdateCommand::CreateInputBuffer(const P4ChangeData &data)
    {
        // Ugly but format must be identical as in spec output

        std::string buffer = "";

        buffer += "Change:";
        buffer += '\t';
        buffer += data.change;
        buffer += '\n';

        buffer += "Date:";
        buffer += '\t';
        buffer += data.creationtime;
        buffer += '\n';

        buffer += "User:";
        buffer += '\t';
        buffer += data.user;
        buffer += '\n';

        buffer += "Status:";
        buffer += '\t';
        buffer += data.status;
        buffer += '\n';

        buffer += "Description:";
        buffer += '\n';

        for(auto &descLine : data.description)
        {
            buffer += '\t';
            buffer += descLine;
            buffer += '\n';
        }

        buffer += "Files:";
        buffer += '\n';

        for(auto &file : data.files)
        {
            buffer += '\t';
            buffer += file;
            buffer += '\n';
        }

        return std::move(buffer);
    }
}
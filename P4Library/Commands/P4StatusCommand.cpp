#include "P4StatusCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
    P4StatusCommand::P4StatusCommand() :
        P4Command("fstat")
    {
    }

    bool P4StatusCommand::Run(P4Task &task)
    {
        m_files.clear();

        CommandArgs myArgs;

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

        for(auto &f : m_paths)
        {
            myArgs.emplace_back(f);
        }

        return task.runP4Command("fstat", myArgs, this);
    }

    void P4StatusCommand::SafeDictAssign(StrDict *varList, const std::string &key, std::string &dest)
    {
        if(!varList)
            return;

        StrPtr *ptr = varList->GetVar(key.c_str());
        if(!ptr)
            return;

        dest = ptr->Text();
    }

	void P4StatusCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while (std::getline(stream, line))
		{
			printf("P4StatusCommand %s\n", line.c_str());
		}
	}

	P4Action P4StatusCommand::getActionFromString(const std::string &str)
	{
		if (str == "add")              { return P4Action::Add; }
		else if (str == "archive")     { return P4Action::Archive; }
		else if (str == "branch")      { return P4Action::Branch; }
		else if (str == "delete")      { return P4Action::Delete; }
		else if (str == "edit")        { return P4Action::Edit; }
		else if (str == "import")      { return P4Action::Import; }
		else if (str == "integrate")   { return P4Action::Integrate; }
		else if (str == "purge")       { return P4Action::Purge; }
		else if (str == "move/delete") { return P4Action::MoveDelete; }		
		else if (str == "move/add")    { return P4Action::MoveAdd; }
		else
		{
			return P4Action::Unknown;
		}
	}

	void P4StatusCommand::OutputError(const char *errBuf)
	{
		printf("%s\n", errBuf);
	}

    void P4StatusCommand::OutputStat(StrDict *varList)
    {
        StrPtr *depotFile = varList->GetVar("depotFile");
		StrPtr *clientFile = varList->GetVar("clientFile");

		if (depotFile || clientFile)
        {
			std::string key = (depotFile) ? depotFile->Text() : clientFile->Text();

            if(!key.empty())
            {
                SafeDictAssign(varList, "depotFile", m_files[key].depotFile);
                SafeDictAssign(varList, "clientFile", m_files[key].clientFile);

				StrPtr *action = varList->GetVar("action");
				if (action)
				{
					m_files[key].action = getActionFromString(action->Text());
				}

				StrPtr *head = varList->GetVar("headAction");
				if (head)
				{
					m_files[key].headAction = getActionFromString(head->Text());
				}
				
				SafeDictAssign(varList, "type", m_files[key].type);
                SafeDictAssign(varList, "headType", m_files[key].headType);
                SafeDictAssign(varList, "headTime", m_files[key].headTime);
                SafeDictAssign(varList, "headRev", m_files[key].headRev);
                SafeDictAssign(varList, "headChange", m_files[key].headChange);
                SafeDictAssign(varList, "headModTime", m_files[key].headModTime);

				SafeDictAssign(varList, "haveRev", m_files[key].haveRev);

                SafeDictAssign(varList, "otherOpen", m_files[key].otherOpen);
                if(!m_files[key].otherOpen.empty())
                {
                    int numOthers = atoi(m_files[key].otherOpen.c_str());

                    for(int i = 0; i < numOthers; i++)
                    {
                        SafeDictAssign(varList, "otherOpen" + std::to_string(i), m_files[key].others[i].otherOpen);
                        SafeDictAssign(varList, "otherAction" + std::to_string(i), m_files[key].others[i].otherAction);
                        SafeDictAssign(varList, "otherChange" + std::to_string(i), m_files[key].others[i].otherChange);
                    }
                }

                m_files[key].isMapped = (m_files[key].depotFile.length() > 0);
            }
			else
			{
				m_files[key].isMapped = false;
				printf("Key for file status cannot be resolved from depotFile field because it's empty!\n");
			}
        }
        else
        {
            printf("depotFile field not found during P4StatusCommand!\n");
        }
    }
}
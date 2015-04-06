
#include "P4StatusCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
	P4StatusCommand::P4StatusCommand() : 
		P4Command("status")
	{
	}

	bool P4StatusCommand::Run(P4Task &task, const CommandArgs &args)
	{
		m_files.clear();

		CommandArgs myArgs;

		for(auto &f : m_paths)
		{
			myArgs.emplace_back(f);
		}

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

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

	void P4StatusCommand::OutputStat(StrDict *varList)
	{
		StrPtr *depotFile = varList->GetVar("depotFile");
		if(depotFile)
		{
			std::string key(depotFile->Text());

			if(!key.empty())
			{
				SafeDictAssign(varList, "depotFile", m_files[key].depotFile);
				SafeDictAssign(varList, "clientFile", m_files[key].clientFile);
				SafeDictAssign(varList, "headAction", m_files[key].headAction);
				SafeDictAssign(varList, "headType", m_files[key].headType);
				SafeDictAssign(varList, "headTime", m_files[key].headTime);
				SafeDictAssign(varList, "headRev", m_files[key].headRev);
				SafeDictAssign(varList, "headChange", m_files[key].headChange);
				SafeDictAssign(varList, "headModTime", m_files[key].headModTime);

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

				m_files[key].isMapped = (m_files[key].clientFile.length() > 0);
			}			
			else
			{
				m_files[key].isMapped = false;

				printf("key for file status cannot be resolved from depotFile field because it's empty!!\n");
			}
		}
		else
		{
			printf("depotFile field not found during P4StatusCommand!\n");
		}
	}
}

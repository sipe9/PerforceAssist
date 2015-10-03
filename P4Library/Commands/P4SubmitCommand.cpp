#include "P4SubmitCommand.hpp"

#include "../Utils/StringUtil.hpp"
#include "../Utils/PathUtil.hpp"

#include <sstream>

namespace VersionControl
{
    P4SubmitCommand::P4SubmitCommand(const std::string &changelist, bool revertUnchanged) :
        P4Command("submit"),
		m_changelist(changelist),
		m_revertUnchanged(revertUnchanged),
		submitting(false),
		lockingFiles(false),
		submitted(false)
    {
    }

    bool P4SubmitCommand::Run(P4Task &task)
    {
        CommandArgs myArgs;
		
        if(!m_changelist.empty())
        {			
			myArgs.emplace_back("-c");
			myArgs.emplace_back(m_changelist);
        }

		if (m_revertUnchanged)
		{
			myArgs.emplace_back("-f");
			myArgs.emplace_back("revertunchanged");
		}

        std::copy(m_customArgs.begin(), m_customArgs.end(), std::back_inserter(myArgs));

		for (auto &path : m_paths)
		{
			myArgs.emplace_back(path);
		}

        return task.runP4Command("submit", myArgs, this);
    }

    void P4SubmitCommand::OutputInfo(char level, const char *data)
    {
        std::stringstream stream(data);
        std::string line;

        while(std::getline(stream, line))
        {
			if (StringUtil::startsWith(line, "Submitting change"))
			{
				submitting = true;
			}
			else if (submitting && StringUtil::startsWith(line, "Locking "))
			{
				lockingFiles = true;
			}
			else if (StringUtil::endsWith(line, "submitted."))
			{
				submitted = true;
			}

			if (lockingFiles)
			{
				if (StringUtil::Contains(line, "//"))
				{
					size_t splitpos = line.find_first_of("//");
					if (splitpos != std::string::npos)
					{
						auto tmp = line.substr(splitpos, line.length() - splitpos);
						std::string depotFilename = PathUtil::parsePathFromString(tmp);
						m_submittedFiles[depotFilename] = P4SubmitResult::Submitted;
					}
				}
			}
        }
    }
}
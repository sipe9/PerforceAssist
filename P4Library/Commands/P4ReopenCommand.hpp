#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <string>
#include <unordered_map>

namespace VersionControl
{
	enum class P4ReopenResult : int
	{
		Reopened = 0,
		Failed,
	};
	
    class P4ReopenCommand : public P4Command
    {
    public:

        P4ReopenCommand(const std::string &changelist);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4ReopenResult> &GetFiles() const { return m_reopenedFiles; }

        void SetChangelist(const std::string &changelist);

    private:

		P4ReopenResult MessageToAddResult(const std::string &message);

        std::string		m_changelist;

        std::unordered_map<std::string, P4ReopenResult>	m_reopenedFiles;
    };
}
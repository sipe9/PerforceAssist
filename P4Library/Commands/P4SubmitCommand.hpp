#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <string>
#include <unordered_map>

namespace VersionControl
{
    enum class P4SubmitResult : int
    {
        Submitted = 0,
        Unknown,
    };

    class P4SubmitCommand : public P4Command
    {
    public:

		P4SubmitCommand(const std::string &changelist, bool revertUnchanged = true);

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4SubmitResult> &GetSubmittedFiles() const { return m_submittedFiles; }

    private:

        std::unordered_map<std::string, P4SubmitResult>	m_submittedFiles;

        std::string		m_changelist;
		bool			m_revertUnchanged;

		bool			submitting;
		bool			lockingFiles;
		bool			submitted;
    };
}
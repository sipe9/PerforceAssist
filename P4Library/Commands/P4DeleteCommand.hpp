#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    enum class P4DeleteResult : int
    {
        OpenedForDeleted = 0,
		NotInClient,
		CantDeleteOpenForAdd,
        Unknown,
    };

    class P4DeleteCommand : public P4Command
    {
    public:

        P4DeleteCommand(std::string changelist = "");

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4DeleteResult> &GetFiles() const { return m_files; }        

    private:
	
		P4DeleteResult MessageToAddResult(const std::string &message);

        std::string		m_changelist;

        std::unordered_map<std::string, P4DeleteResult>	m_files;
    };
}
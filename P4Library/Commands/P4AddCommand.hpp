#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    enum class P4AddResult : int
    {
        OpenedForAdd = 0,
        AlreadyOpenedForAdd,
        AlreadyOpenedForEdit,
        AlreadyExists,
        Unknown,
    };

    class P4AddCommand : public P4Command
    {
    public:

        P4AddCommand(std::string changelist = "");

        virtual bool Run(P4Task &task);

        void OutputInfo(char level, const char *data);

        const std::unordered_map<std::string, P4AddResult> &GetFiles() const { return m_files; }

        P4AddResult MessageToAddResult(const std::string &message);

    private:

        std::string		m_changelist;

        std::unordered_map<std::string, P4AddResult>	m_files;
    };
}
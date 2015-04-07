#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
    struct P4FileStatusOther
    {
        std::string otherOpen;
        std::string otherAction;
        std::string otherChange;
    };

    struct P4FileStatus
    {
        bool isMapped;

        std::string depotFile;
        std::string clientFile;
        std::string headAction;
        std::string headType;
        std::string headTime;
        std::string headRev;
        std::string headChange;
        std::string headModTime;
        std::string otherOpen;

        std::unordered_map<int, P4FileStatusOther> others;
    };

    class P4StatusCommand : public P4Command
    {
    public:

        P4StatusCommand();

        virtual bool Run(P4Task &task);

        void OutputStat(StrDict *varList);

        const std::unordered_map<std::string, P4FileStatus> &GetFiles() const { return m_files; }

    private:

        void	SafeDictAssign(StrDict *varList, const std::string &key, std::string &dest);

        std::unordered_map<std::string, P4FileStatus> m_files;
    };
}
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
		P4Action action;
		P4Action headAction;
		std::string type;
        std::string headType;
        std::string headTime;
        std::string headRev;
        std::string headChange;
        std::string headModTime;
		std::string haveRev;
        std::string otherOpen;

        std::unordered_map<int, P4FileStatusOther> others;

		P4FileStatus() : 
			isMapped(false),
			action(P4Action::Unknown),
			headAction(P4Action::Unknown)
		{
		}
    };

    class P4StatusCommand : public P4Command
    {
    public:

        P4StatusCommand();

        virtual bool Run(P4Task &task);

		void OutputError(const char *errBuf);

		void OutputInfo(char level, const char *data);

        void OutputStat(StrDict *varList);		

        const std::unordered_map<std::string, P4FileStatus> &GetFiles() const { return m_files; }

    private:

        void	SafeDictAssign(StrDict *varList, const std::string &key, std::string &dest);

		P4Action		getActionFromString(const std::string &str);
		
        std::unordered_map<std::string, P4FileStatus> m_files;
    };
}
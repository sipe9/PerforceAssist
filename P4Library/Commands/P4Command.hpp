#pragma once

#include <string>
#include <vector>

#include "p4/clientapi.h"

namespace VersionControl
{
	enum class P4Action
	{
		Add,
		Edit,
		Delete,
		Branch,
		MoveAdd,
		MoveDelete,
		Integrate,
		Import,
		Purge,
		Archive,
		Unknown,
	};

    typedef std::vector<std::string> CommandArgs;

    class P4Task;

    class P4Command : public ClientUser
    {
    public:

        // ClientUser overrides
        void HandleError(Error *err);
        void OutputError(const char *errBuf);
        void ErrorPause(char *errBuf, Error *e);
        void OutputInfo(char level, const char *data);
        void OutputStat(StrDict *varList);
        void OutputText(const char *data, int length);
        void OutputBinary(const char *data, int length);
        void InputData(StrBuf *strbuf, Error *e);
        void Prompt(const StrPtr &msg, StrBuf &rsp, int noEcho, Error *e);
        void Finished();

        virtual bool Run(P4Task &task) = 0;

        void AddPath(const std::string &filename);
        void AddPaths(const std::vector<std::string> &files);

        void AddCustomArgument(const std::string &arg);

		bool HasPaths() { return m_paths.size() > 0; }
		bool HasCustomArguments() { return m_customArgs.size() > 0; }

		const std::string &GetName() const { return m_name; }

    protected:

        P4Command(const char *name);

		std::string					m_name;
        std::vector<std::string>	m_paths;
        std::vector<std::string>    m_customArgs;
    };
}
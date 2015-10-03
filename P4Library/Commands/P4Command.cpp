#include "P4Command.hpp"

#if defined(_WINDOWS)
#include <windows.h>
#else
#error Not implemented
#endif

#include <sstream>

namespace VersionControl
{
    P4Command::P4Command(const char *name) :
		m_name(name)
    {
    }

    void P4Command::HandleError(Error *err)
    {
        if(err == NULL)
        {
            printf("Cannot handle error because it's null!\n");
            return;
        }

        if(err->IsError() || err->IsFatal())
        {
            StrBuf buffer;
            err->Fmt(&buffer);
            std::string text(buffer.Text());
            printf("%s\n", text.c_str());
        }
    }

    void P4Command::OutputError(const char *errBuf)
    {
        printf("%s\n", errBuf);
    }

    void P4Command::ErrorPause(char *errBuf, Error *e)
    {
        printf("%s\n", errBuf);
    }

    void P4Command::OutputInfo(char level, const char *data)
    {
        std::stringstream stream;
        stream << data << "( " << (int)level << ")";
        printf("%s\n", stream.str().c_str());
    }

    void P4Command::OutputStat(StrDict *varList)
    {
        printf("OutputStat!\n");
    }

    void P4Command::OutputText(const char *data, int length)
    {
        printf("OutputText!\n");
    }

    void P4Command::OutputBinary(const char *data, int length)
    {
        printf("OutputBinary!\n");
    }

    void P4Command::InputData(StrBuf *strbuf, Error *e)
    {
        printf("InputData!\n");
    }

    void P4Command::Prompt(const StrPtr &msg, StrBuf &rsp, int noEcho, Error *e)
    {
        printf("Prompt!\n");
    }

    void P4Command::Finished()
    {
    }

    void P4Command::AddPath(const std::string &filename)
    {
        m_paths.emplace_back(filename);
    }

    void P4Command::AddPaths(const std::vector<std::string> &files)
    {
        for(auto &path : files)
        {
            m_paths.emplace_back(path);
        }
    }

    void P4Command::AddCustomArgument(const std::string &arg)
    {
        m_customArgs.emplace_back(arg);
    }
}
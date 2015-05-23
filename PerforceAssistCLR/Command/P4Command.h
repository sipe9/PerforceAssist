#pragma once

#include "../P4Task.h"

namespace PerforceAssist
{
    public ref class P4Command abstract
    {
    public:
        P4Command(System::String ^name);
        ~P4Command();

        virtual bool        run(P4Task ^task) = 0;

    private:

        System::String      ^m_name;
    };
}

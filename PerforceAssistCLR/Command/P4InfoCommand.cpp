#include "P4InfoCommand.h"
#include "../STLWrapper.h"

#include "Commands\P4InfoCommand.hpp"

#include <Windows.h>
#include <msclr/marshal_cppstd.h>

#include <vector>
#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace PerforceAssist
{
    P4InfoCommand::P4InfoCommand() : P4Command("info") {}
    P4InfoCommand::~P4InfoCommand() {}

    bool P4InfoCommand::run(P4Task ^task)
    {
        VersionControl::P4InfoCommand *cmd = new VersionControl::P4InfoCommand();        

        if(!task->getTask()->runCommand(*cmd))
        {
            return false;
        }

        m_info = gcnew P4Info(cmd->GetP4Info());

        delete cmd;

        return true;
    }
}
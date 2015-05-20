#include "P4CommandWrapper.h"
#include "STLWrapper.h"

#include "Commands\P4InfoCommand.hpp"

#include <Windows.h>
#include <msclr/marshal_cppstd.h>

#include <vector>
#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace PerforceAssist
{
    P4CommandWrapper::P4CommandWrapper()
    {
    }

    P4CommandWrapper::~P4CommandWrapper()
    {
    }

    P4InfoWrapper^ P4CommandWrapper::runInfoCommand(P4TaskWrapper ^task)
    {
        // Run native
        VersionControl::P4InfoCommand *cmd = new VersionControl::P4InfoCommand();        
        task->getTask()->runCommand(*cmd);
        VersionControl::P4Info managedInfo = cmd->GetP4Info();

        // To managed
        P4InfoWrapper ^info = gcnew P4InfoWrapper(managedInfo);

        delete cmd;

        return info;
    }

    List<System::String^> ^P4CommandWrapper::testStrings()
    {
        std::vector<std::string> stdStrings;
        stdStrings.emplace_back("String1");
        stdStrings.emplace_back("String2");
        stdStrings.emplace_back("String3");

        List<System::String^> ^managedStrings = STLWrapper::ToList(stdStrings);
        return managedStrings;
    }
}
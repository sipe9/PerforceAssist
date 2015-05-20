#pragma once

#include "Commands\P4InfoCommand.hpp"

#include "P4TaskWrapper.h"
#include "P4Structs.h"

using namespace System::Collections::Generic;

namespace PerforceAssist
{
    public ref class P4CommandWrapper
	{

    public:

        P4CommandWrapper();
        ~P4CommandWrapper();      

        P4InfoWrapper           ^runInfoCommand(P4TaskWrapper ^task);
        List<System::String^>   ^testStrings();

	};
}

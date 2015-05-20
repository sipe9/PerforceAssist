#pragma once

#include <cliext/adapter>
#include <cliext\vector>

#include <vector>
#include <string>

#include <Windows.h>
#include <msclr/marshal_cppstd.h>

using namespace System::Collections::Generic;

namespace PerforceAssist
{
    public ref class STLWrapper
	{
    public:

        static System::String ^ToString(std::string &str)
        {
            return gcnew System::String(str.c_str());
        }

        static std::string ToString(System::String ^str)
        {
            return msclr::interop::marshal_as<std::string>(str);
        }

        static List<System::String^> ^ToList(std::vector<std::string> &strings)
        {
            List<System::String^> ^list = gcnew List<System::String^>(strings.size());

            for(auto &str : strings)
            {
                list->Add(STLWrapper::ToString(str));
            }            

            return list;
        }
	};
}

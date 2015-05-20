#pragma once



#include <string>
#include <vector>

namespace VersionControl
{
    namespace PathUtil
    {
        std::string parseDepotPathFromString(const std::string &from);

        void ConvertToForwardSlashes(std::string &path);        

        bool IsValidDepotPath(const std::string &path);
    }
}
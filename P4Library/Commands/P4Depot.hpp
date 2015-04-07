#pragma once

#include <string>
#include <vector>

namespace VersionControl
{
    struct P4DepotData
    {
        std::string depot;
        std::string owner;
        std::string date;
        std::vector<std::string> description;
        std::string type;
        std::string map;
    };
}
#pragma once

#include <string>

namespace VersionControl
{
    struct P4ChangeData
    {
        std::string change;
        std::string creationtime;
        std::string client;
        std::string user;
        std::string status;

        std::vector<std::string> description;
        std::vector<std::string> files;
    };
}
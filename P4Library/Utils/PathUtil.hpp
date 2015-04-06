
#pragma once

#include <string>
#include <vector>

class PathUtil
{
public:

	//static std::string WorkspaceToDepot(const std::string &root, const std::string &workspacePath);

	static void ConvertToForwardSlashes(std::string &path);

	static bool IsValidDepotPath(const std::string &path);
};

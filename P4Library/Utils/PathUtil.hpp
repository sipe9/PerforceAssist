
#pragma once

#include <string>
#include <vector>

namespace VersionControl
{
	class PathUtil
	{
	public:

		static std::string parseDepotPathFromString(const std::string &from);

		static void ConvertToForwardSlashes(std::string &path);

		static bool IsValidDepotPath(const std::string &path);
	};
}
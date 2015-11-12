
#pragma once

#include <string>
#include <vector>

namespace VersionControl
{
	class PathUtil
	{
	public:

		static std::string parsePathFromString(const std::string &from, bool isDrivePath = false);

		static void ConvertToForwardSlashes(std::string &path);

		static bool IsValidDepotPath(const std::string &path);

		static std::string GetAbsolutePath(const std::string &path);
		static bool PathExists(const std::string &path);
	};
}
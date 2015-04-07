
#include "PathUtil.hpp"
#include "StringUtil.hpp"

namespace VersionControl
{
	bool PathUtil::IsValidDepotPath(const std::string &path)
	{
		if (!StringUtil::startsWith(path, "//"))
		{
			return false;
		}

		return true;
	}

	void PathUtil::ConvertToForwardSlashes(std::string &path)
	{
		for (unsigned i = 0; i < path.length(); i++)
		{
			if (path[i] == '\\')
			{
				path[i] = '/';
			}
		}
	}

	std::string PathUtil::parseDepotPathFromString(const std::string &from)
	{
		std::string tmp = from;

		// Split by default from revision number
		char splitChar = '#';

		// If not revision number, fall back to whitespace
		if (!StringUtil::Contains(tmp, "#"))
		{
			splitChar = ' ';
		}

		// First identify file extension position from string
		size_t extpos = tmp.find_last_of(splitChar);

		if (extpos == std::string::npos)
		{
			printf("Failed to parse depot filename from %s, couldn't find file extension!\n", from.c_str());
			return from;
		}

		// Step from file extension position until we hit our split character (# or ' ')
		int nextSplitPosAfterExt = -1;
		for (unsigned i = extpos; i < tmp.length(); i++)
		{
			if (tmp[i] == splitChar)
			{
				nextSplitPosAfterExt = i;
				break;
			}
		}

		// Check that we actually found our next split position
		if (nextSplitPosAfterExt != -1)
		{
			tmp = tmp.substr(0, nextSplitPosAfterExt);
		}
		else
		{
			printf("Failed to parse depot filename from %s, couldn't find revision or whitespace after file extension!\n", from.c_str());
			return from;
		}

		// Make sure that path starts with double forward slashes like proper depot path
		int splitpos = tmp.find("//");
		if (splitpos == std::string::npos)
		{
			printf("Filename %s doesn't contain proper depot backslashes and it might cause issues!\n", tmp.c_str());
		}
		else if (splitpos > 0)
		{
			tmp = tmp.substr(splitpos, tmp.length() - splitpos);
		}

		// Validate that this is valid depot path
		if (!IsValidDepotPath(tmp))
		{
			printf("Warning, depot filename might be in incorrect format! (%s)", tmp.c_str());
		}

		return tmp;
	}
}
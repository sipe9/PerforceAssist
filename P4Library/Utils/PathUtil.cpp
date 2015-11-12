
#include "PathUtil.hpp"
#include "StringUtil.hpp"

#include <windows.h>
#include <Shlwapi.h>

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

	std::string PathUtil::parsePathFromString(const std::string &from, bool isDrivePath)
	{
		std::string tmp = from;

		// Trim end and remove . if ends with
		tmp = StringUtil::TrimEnd(tmp, ' ');
		if (StringUtil::endsWith(tmp, "."))
		{
			tmp = StringUtil::TrimEnd(tmp, '.');
		}

		// Split by default from revision number
		char splitChar = '#';

		// If not revision number, fall back to whitespace
		if (!StringUtil::Contains(tmp, "#"))
		{
			splitChar = ' ';
		}

		// First identify file extension position from string
		size_t extpos = tmp.find_last_of('.');
		if (extpos == std::string::npos)
		{
			size_t lastslash = tmp.find_last_of('/');

			if (lastslash == std::string::npos)
			{
				printf("Failed to parse depot filename from %s, couldn't find file extension!\n", from.c_str());
				return from;
			}
			else
			{
				extpos = lastslash;
			}
		}

		// Step from file extension position until we hit our split character (# or ' ')
		int nextSplitPosAfterExt = -1;
		for (size_t i = extpos; i < tmp.length(); i++)
		{
			if (tmp[i] == splitChar)
			{
				nextSplitPosAfterExt = static_cast<int>(i);
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

		tmp = StringUtil::Trim(tmp, ' ');
		tmp = StringUtil::Trim(tmp, '\t');

		if (!isDrivePath)
		{
			// Make sure that path starts with double forward slashes like proper depot path
			size_t splitpos = tmp.find("//");
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
		}

		return tmp;
	}

	std::string PathUtil::GetAbsolutePath(const std::string &path)
	{
		char *fileExt;
		char szDir[256];
		GetFullPathNameA(path.c_str(), 256, szDir, &fileExt);
		return std::move(std::string(szDir));
	}

	bool PathUtil::PathExists(const std::string &path)
	{
		DWORD dwAttrib = GetFileAttributesA(path.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
}
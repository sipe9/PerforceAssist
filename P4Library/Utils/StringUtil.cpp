
#include "StringUtil.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace VersionControl
{
	bool StringUtil::endsWith(const std::string &from, const std::string &what)
	{
		if (from.length() < what.length())
			return false;

		std::string::const_reverse_iterator i1 = from.rbegin();
		std::string::const_reverse_iterator i2 = what.rbegin();

		for (; i2 != what.rend(); i2++, i1++)
		{
			if (*i1 != *i2)
				return false;
		}

		return true;
	}

	bool StringUtil::startsWith(const std::string &from, const std::string &what)
	{
		if (from.length() < what.length())
			return false;

		std::string::const_iterator i1 = from.begin();
		std::string::const_iterator i2 = what.begin();

		for (; i2 != what.end(); i2++, i1++)
		{
			if (*i1 != *i2)
				return false;
		}

		return true;
	}

	std::string StringUtil::SplitByLastOf(const std::string &s, const char lastOf, bool keepFirst)
	{
		size_t splitpos = s.find_last_of(lastOf);

		if (splitpos == std::string::npos)
			return s;

		if (keepFirst)
			return s.substr(0, splitpos);
		else
			return s.substr(splitpos + 1, s.length() - splitpos - 1);
	}

	std::string StringUtil::SplitByFirstOf(const std::string &s, const char firstOf, bool keepFirst)
	{
		size_t splitpos = s.find_first_of(firstOf);

		if (splitpos == std::string::npos)
			return s;

		if (keepFirst)
			return s.substr(0, splitpos);
		else
			return s.substr(splitpos + 1, s.length() - splitpos - 1);
	}

	bool StringUtil::Contains(const std::string &s, const std::string &string)
	{
		return (s.find(string) != std::string::npos);
	}

	std::string StringUtil::TrimEnd(const std::string &str, char c)
	{
		std::string::size_type i1 = str.length() - 1;

		while (i1 >= 0 && str[i1] == c)
		{
			--i1;
		}

		if (i1 < 0)
			return "";

		return str.substr(0, i1 + 1);
	}

	std::string StringUtil::TrimStart(const std::string &str, char c)
	{
		std::string::size_type iend = str.length();
		std::string::size_type i1 = 0;

		while (i1 < iend && str[i1] == c)
		{
			++i1;
		}

		if (i1 >= iend)
			return "";

		return str.substr(i1);
	}

	std::string StringUtil::Trim(const std::string &str, char c)
	{
		return TrimStart(TrimEnd(str, c), c);
	}

	void StringUtil::Split(std::string &s, const char delim, std::vector<std::string> &out)
	{
		std::string::size_type lastPos = s.find_first_not_of(delim, 0);
		std::string::size_type pos = s.find_first_of(delim, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			out.push_back(s.substr(lastPos, pos - lastPos));
			lastPos = s.find_first_not_of(delim, pos);
			pos = s.find_first_of(delim, lastPos);
		}
	}

	bool StringUtil::IsPositiveNumber(const std::string &s)
	{
		return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
	}

	bool StringUtil::startsWithAndAssign(const std::string &line, const char *prefix, std::string &dest, bool trim)
	{
		if (StringUtil::startsWith(line, prefix))
		{
			dest = line.substr(strlen(prefix));

			if (trim)
			{
				dest = TrimStart(dest, ' ');
				dest = TrimStart(dest, '\t');
			}

			return true;
		}
		return false;
	}

	std::string StringUtil::Substring(const std::string &s, int start, int length)
	{
		if ((start + length) > static_cast<int>(s.length()))
			return s;

		return s.substr(start, length);
	}
}
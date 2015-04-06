
#pragma once

#include <string>
#include <vector>

class StringUtil
{
public:

	static bool endsWith(const std::string &from, const std::string &what);
	static bool startsWith(const std::string &from, const std::string &what);

	static std::string TrimEnd(const std::string& str, char c);
	static std::string TrimStart(const std::string &str, char c);
	static std::string Trim(const std::string &str, char c);

	static std::string SplitByLastOf(const std::string &s, const char lastOf, bool keepFirst);
	static std::string SplitByFirstOf(const std::string &s, const char firstOf, bool keepFirst);
	static bool Contains(const std::string &s, const std::string &string);
	static void Split(std::string &s, const char delim, std::vector<std::string> &out);
	static bool IsPositiveNumber(const std::string &s);
};

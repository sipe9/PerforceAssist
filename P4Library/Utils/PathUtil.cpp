
#include "PathUtil.hpp"
#include "StringUtil.hpp"

bool PathUtil::IsValidDepotPath(const std::string &path)
{
	if(!StringUtil::startsWith(path, "//"))
	{		
		return false;
	}

	return true;
}

/*std::string PathUtil::WorkspaceToDepot(const std::string &root, const std::string &workspacePath)
{
	if(!IsValidDepotPath(root))
	{
		printf("Invalid depot path %s! Path must start with double forward slashes!\n");
		return workspacePath;
	}

	// Get rid of the forward slashes from the beginning
	std::string r = root.substr(2, root.length() - 2);

	std::string wp = workspacePath;
	ConvertToForwardSlashes(wp);

	// Get rid of the drive letter from the beginning
	wp = StringUtil::SplitByFirstOf(wp, '/', false);

	std::vector<std::string> rootSplit, wpSplit;
	StringUtil::Split(r, '/', rootSplit);
	StringUtil::Split(wp, '/', wpSplit);

	for(unsigned i = 0; i < wpSplit.size(); i++)
	{
	}

	return wp;
}*/

void PathUtil::ConvertToForwardSlashes(std::string &path)
{
	for(unsigned i = 0; i < path.length(); i++)
	{
		if(path[i] == '\\')
		{
			path[i] = '/';
		}
	}
}


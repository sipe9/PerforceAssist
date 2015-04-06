
#pragma once

#include <string>
#include <vector>

namespace VersionControl
{
	struct P4ClientData
	{
		std::string		client;
		std::string		update;
		std::string		access;
		std::string		owner;
		std::string		host;
		std::vector<std::string>		description;
		std::string		root;

		std::vector<std::string>		options;

		std::string		submitOptions;
		std::string		lineEnd;

		std::vector<std::string>	view;
	};
}

#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

#include <unordered_map>

namespace VersionControl
{
	struct P4ClientResult
	{
		std::string		client;
		std::string		update;
		std::string		access;
		std::string		owner;
		std::string		host;
		std::string		description;
		std::string		root;

		std::vector<std::string>		options;

		std::string		submitOptions;
		std::string		lineEnd;

		std::vector<std::string>	view;
	};

	class P4ClientCommand : public P4Command
	{

	public:		

		P4ClientCommand(const std::string &client);

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);		

		const P4ClientResult &GetClientResult() const { return m_clientResult; }

	private:
		
		std::string		m_client;

		P4ClientResult	m_clientResult;
	};
}

#include "P4ClientUpdateCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{	
	// todo: move to proper place
	static const char* g_Client = "Client:";
	static const char* g_Update = "Update:";
	static const char* g_Access = "Access:";
	static const char* g_Owner = "Owner:";
	static const char* g_Host = "Host:";
	static const char* g_Description = "Description:";
	static const char* g_Root = "Root:";
	static const char* g_Options = "Options:";
	static const char* g_SubmitOptions = "SubmitOptions:";
	static const char* g_LineEnd = "LineEnd:";
	static const char* g_View = "View:";

	static const char* g_savedPrefix = "Client ";
	static const char* g_savedSuffix = " saved.";

	P4ClientUpdateCommand::P4ClientUpdateCommand(const P4ClientData &data) : 
		P4Command("client"),
		m_clientData(data),
		m_clientUpdated(false)
	{
	}

	bool P4ClientUpdateCommand::Run(P4Task &task, const CommandArgs &args)
	{
		CommandArgs myArgs;

		myArgs.emplace_back("-i");

		std::copy(args.begin(), args.end(), std::back_inserter(myArgs));

		return task.runP4Command("client", myArgs, this);
	}

	void P4ClientUpdateCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;

		while(std::getline(stream, line))
		{
			if(StringUtil::startsWith(line, g_savedPrefix) && 
				StringUtil::endsWith(line, g_savedSuffix))
			{
				m_clientUpdated = true;
			}	
			else
			{
				m_clientUpdated = false;
				printf("Failed to update client specifications! %s\n", line.c_str());
			}
		}
	}

	void P4ClientUpdateCommand::InputData(StrBuf *strbuf, Error *e)
	{
		std::string buffer = CreateClientInputBuffer(m_clientData);
		strbuf->Set(buffer.c_str());
	}

	std::string P4ClientUpdateCommand::CreateClientInputBuffer(const P4ClientData &clientData)
	{
		// Ugly but format must be identical as in spec output

		std::string buffer = "";

		buffer += g_Client; 
		buffer += '\t';
		buffer += clientData.client;
		buffer += '\n';

		buffer += g_Owner; 
		buffer += '\t';
		buffer += clientData.owner;
		buffer += '\n';

		buffer += g_Host; 
		buffer += '\t';
		buffer += clientData.host;
		buffer += '\n';

		buffer += g_Description;
		buffer += '\n';

		for(auto &descLine : clientData.description)
		{
			buffer += '\t';
			buffer += descLine;
			buffer += '\n';
		}

		buffer += g_Root;
		buffer += '\t';
		buffer += clientData.root;
		buffer += '\n';

		buffer += g_Options; 
		buffer += '\t';

		for(auto &opt : clientData.options)
		{
			buffer += '\t';
			buffer += opt;
		}
		buffer += '\n';

		buffer += g_SubmitOptions;
		buffer += '\t';
		buffer += clientData.submitOptions;
		buffer += '\n';

		buffer += g_LineEnd;
		buffer += '\t';
		buffer += clientData.lineEnd;
		buffer += '\n';

		buffer += g_View;
		buffer += '\n';

		for(auto &view : clientData.view)
		{
			buffer += '\t';
			buffer += view;
			buffer += '\n';
		}

		return std::move(buffer);
	}
}

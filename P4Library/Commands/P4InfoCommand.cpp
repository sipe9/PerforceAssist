
#include "P4InfoCommand.hpp"

#include "../Utils/StringUtil.hpp"

#include <sstream>

namespace VersionControl
{
	static const char* g_ClientName = "Client name: ";
	static const char* g_ClientHost = "Client host: "; 
	static const char* g_ClientRoot = "Client root: "; 
	static const char* g_ClientUnknown = "Client unknown.";
	static const char* g_CurrentDir = "Current directory: ";
	static const char* g_PeerAddr = "Peer address: ";
	static const char* g_ClientAddr = "Client address: ";
	static const char* g_ServerAddr = "Server address: ";
	static const char* g_ServerRoot = "Server root: ";
	static const char* g_ServerVersion = "Server version: ";
	static const char* g_ServerLicense = "Server license: ";
	static const char* g_CaseHandling = "Case Handling: ";

	P4InfoCommand::P4InfoCommand() : 
		P4Command("info") 
	{
	}

	bool P4InfoCommand::Run(P4Task &task, const CommandArgs &args)
	{
		return task.runP4Command("info", args, this);
	}

	bool ParseInfo(const std::string &line, const char *prefix, std::string &dest)
	{
		if (StringUtil::startsWith(line, prefix))
		{
			dest = line.substr(strlen(prefix));
			return true;
		}
		return false;
	}

	void P4InfoCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while(std::getline(stream, line))
		{
			if (ParseInfo(line, g_ClientName, m_info.clientName)) 
				continue;

			if (ParseInfo(line, g_ClientHost, m_info.clientHost)) 
				continue;

			if (ParseInfo(line, g_ClientRoot, m_info.clientRoot)) 
				continue;

			if (ParseInfo(line, g_CurrentDir, m_info.currentDir)) 
				continue;

			if (ParseInfo(line, g_PeerAddr, m_info.peerAddress)) 
				continue;

			if (ParseInfo(line, g_ClientAddr, m_info.clientAddress)) 
				continue;

			if (ParseInfo(line, g_ServerAddr, m_info.serverAddress)) 
				continue;

			if (ParseInfo(line, g_ServerRoot, m_info.serverRoot)) 
				continue;

			if (ParseInfo(line, g_ServerVersion, m_info.serverVersion)) 
				continue;

			if (ParseInfo(line, g_ServerLicense, m_info.serverLicense)) 
				continue;

			if (ParseInfo(line, g_CaseHandling, m_info.caseHandling)) 
				continue;

			if (StringUtil::startsWith(line, g_ClientUnknown)) 
			{
				m_info.clientIsKnown = false;
				continue;
			}
		}
	}
}


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
	static const char* g_Username = "User name: ";
	static const char* g_ServerDate = "Server date: ";
	static const char* g_ServerUptime = "Server uptime: ";

	P4InfoCommand::P4InfoCommand() : 
		P4Command("info") 
	{
	}

	bool P4InfoCommand::Run(P4Task &task, const CommandArgs &args)
	{
		return task.runP4Command("info", args, this);
	}

	void P4InfoCommand::OutputInfo(char level, const char *data)
	{
		std::stringstream stream(data);
		std::string line;
		while(std::getline(stream, line))
		{			
			if (m_info.clientName.empty() && StringUtil::startsWithAndAssign(line, g_ClientName, m_info.clientName))
			{
				m_info.clientIsKnown = true;
				continue;
			}

			if (m_info.clientHost.empty() && StringUtil::startsWithAndAssign(line, g_ClientHost, m_info.clientHost))
				continue;

			if (m_info.clientRoot.empty() && StringUtil::startsWithAndAssign(line, g_ClientRoot, m_info.clientRoot))
				continue;

			if (m_info.currentDir.empty() && StringUtil::startsWithAndAssign(line, g_CurrentDir, m_info.currentDir))
				continue;

			if (m_info.peerAddress.empty() && StringUtil::startsWithAndAssign(line, g_PeerAddr, m_info.peerAddress))
				continue;

			if (m_info.clientAddress.empty() && StringUtil::startsWithAndAssign(line, g_ClientAddr, m_info.clientAddress))
				continue;

			if (m_info.serverAddress.empty() && StringUtil::startsWithAndAssign(line, g_ServerAddr, m_info.serverAddress))
				continue;

			if (m_info.serverRoot.empty() && StringUtil::startsWithAndAssign(line, g_ServerRoot, m_info.serverRoot))
				continue;

			if (m_info.serverVersion.empty() && StringUtil::startsWithAndAssign(line, g_ServerVersion, m_info.serverVersion))
				continue;

			if (m_info.serverLicense.empty() && StringUtil::startsWithAndAssign(line, g_ServerLicense, m_info.serverLicense))
				continue;

			if (m_info.caseHandling.empty() && StringUtil::startsWithAndAssign(line, g_CaseHandling, m_info.caseHandling))
				continue;

			if (m_info.username.empty() && StringUtil::startsWithAndAssign(line, g_Username, m_info.username))
				continue;

			if (m_info.serverDate.empty() && StringUtil::startsWithAndAssign(line, g_ServerDate, m_info.serverDate))
				continue;

			if (m_info.serverUptime.empty() && StringUtil::startsWithAndAssign(line, g_ServerUptime, m_info.serverUptime))
				continue;

			if (StringUtil::startsWith(line, g_ClientUnknown)) 
			{
				m_info.clientIsKnown = false;
				continue;
			}

			// If reached, parse information and store in P4Info struct
			printf("%s\n", line.c_str());
		}
	}
}

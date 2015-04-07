
#pragma once

#include "../P4Task.hpp"
#include "P4Command.hpp"

namespace VersionControl
{
	struct P4Info
	{
		bool clientIsKnown;
		std::string clientName;
		std::string clientHost;
		std::string clientRoot;
		std::string currentDir;
		std::string peerAddress;
		std::string clientAddress;
		std::string serverAddress;
		std::string serverRoot;
		std::string serverVersion;
		std::string serverLicense;
		std::string caseHandling; 
		std::string username;
		std::string serverDate;
		std::string serverUptime;
	};

	class P4InfoCommand : public P4Command
	{

	public:		

		P4InfoCommand();

		virtual bool Run(P4Task &task, const CommandArgs &args);

		void OutputInfo(char level, const char *data);

		const P4Info &GetP4Info() const { return m_info;}

	private:

		P4Info		m_info;
	};
}
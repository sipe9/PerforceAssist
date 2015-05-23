#pragma once

#include "P4Task.hpp"
#include "STLWrapper.h"

namespace PerforceAssist
{
    public ref class P4Task
	{

    public:

        P4Task();
        ~P4Task();

        bool				connect(System::String ^user, System::String ^password);
        bool				disconnect();
        bool				isConnected();

        System::String^		getP4Port();
        System::String^		getP4User();
        System::String^		getP4Client();
        System::String^	    getP4Password();
        System::String^		getP4Host();
        System::String^	    getP4Root();

        void				setP4Port(System::String ^port);
        void				setP4User(System::String ^user);
        void				setP4Client(System::String ^client);
        void				setP4Password(System::String ^password);
        void				setP4Host(System::String ^host);
        void				setP4Root(System::String ^root);

        VersionControl::P4Task *getTask() { return m_p4Task; }

    private:
        
        VersionControl::P4Task *m_p4Task;

	};
}

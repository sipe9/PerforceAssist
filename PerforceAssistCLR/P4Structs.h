#pragma once

#include "Commands\P4InfoCommand.hpp"

namespace PerforceAssist
{
    enum P4AddResult : int
    {
        OpenedForAdd = 0,
        AlreadyOpenedForAdd,
        AlreadyOpenedForEdit,
        AlreadyExists,
        Unknown,
    };

    public ref struct P4InfoWrapper
    {
    public:

        bool clientIsKnown;
        System::String ^clientName;
        System::String ^clientHost;
        System::String ^clientRoot;
        System::String ^currentDir;
        System::String ^peerAddress;
        System::String ^clientAddress;
        System::String ^serverAddress;
        System::String ^serverRoot;
        System::String ^serverVersion;
        System::String ^serverLicense;
        System::String ^caseHandling;
        System::String ^username;
        System::String ^serverDate;
        System::String ^serverUptime;

        P4InfoWrapper::P4InfoWrapper(VersionControl::P4Info &info)
        {
            this->clientIsKnown = info.clientIsKnown;
            this->clientName = gcnew System::String(info.clientName.c_str());
            this->clientHost = gcnew System::String(info.clientHost.c_str());
            this->clientRoot = gcnew System::String(info.clientRoot.c_str());
            this->currentDir = gcnew System::String(info.currentDir.c_str());
            this->peerAddress = gcnew System::String(info.peerAddress.c_str());
            this->clientAddress = gcnew System::String(info.clientAddress.c_str());
            this->serverAddress = gcnew System::String(info.serverAddress.c_str());
            this->serverRoot = gcnew System::String(info.serverRoot.c_str());
            this->serverVersion = gcnew System::String(info.serverVersion.c_str());
            this->serverLicense = gcnew System::String(info.serverLicense.c_str());
            this->caseHandling = gcnew System::String(info.caseHandling.c_str());
            this->username = gcnew System::String(info.username.c_str());
            this->serverDate = gcnew System::String(info.serverDate.c_str());
            this->serverUptime = gcnew System::String(info.serverUptime.c_str());
        }
    };
}
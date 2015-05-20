#include "P4TaskWrapper.h"
#include "STLWrapper.h"

#include "Commands\P4InfoCommand.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace PerforceAssist
{
    P4TaskWrapper::P4TaskWrapper() :
        m_p4Task(new VersionControl::P4Task())
    {
    }

    P4TaskWrapper::~P4TaskWrapper()
    {
        if(m_p4Task)
        {
            delete m_p4Task;
            m_p4Task = 0;
        }
    }

    bool P4TaskWrapper::connect(System::String ^user, System::String ^password)
    {
        return m_p4Task->connect(STLWrapper::ToString(user), STLWrapper::ToString(password));
    }

    bool P4TaskWrapper::disconnect()
    {
        return m_p4Task->disconnect();
    }

    bool P4TaskWrapper::isConnected()
    {
        return m_p4Task->isConnected();
    }

    System::String^ P4TaskWrapper::getP4Port()
    {
        return gcnew System::String(m_p4Task->getP4Port().c_str());
    }

    System::String^ P4TaskWrapper::getP4User()
    {
        return gcnew System::String(m_p4Task->getP4User().c_str());
    }

    System::String^ P4TaskWrapper::getP4Client()
    {
        return gcnew System::String(m_p4Task->getP4Client().c_str());
    }

    System::String^ P4TaskWrapper::getP4Password()
    {
        return gcnew System::String(m_p4Task->getP4Password().c_str());
    }

    System::String^ P4TaskWrapper::getP4Host()
    {
        return gcnew System::String(m_p4Task->getP4Host().c_str());
    }

    System::String^ P4TaskWrapper::getP4Root()
    {
        return gcnew System::String(m_p4Task->getP4Root().c_str());
    }

    void P4TaskWrapper::setP4Port(System::String ^port)
    {
        return m_p4Task->setP4Port(STLWrapper::ToString(port));
    }

    void P4TaskWrapper::setP4User(System::String ^user)
    {
        return m_p4Task->setP4User(STLWrapper::ToString(user));
    }

    void P4TaskWrapper::setP4Client(System::String ^client)
    {
        return m_p4Task->setP4Client(STLWrapper::ToString(client));
    }

    void P4TaskWrapper::setP4Password(System::String ^password)
    {
        return m_p4Task->setP4Password(STLWrapper::ToString(password));
    }

    void P4TaskWrapper::setP4Host(System::String ^host)
    {
        return m_p4Task->setP4Host(STLWrapper::ToString(host));
    }

    void P4TaskWrapper::setP4Root(System::String ^root)
    {
        return m_p4Task->setP4Root(STLWrapper::ToString(root));
    }
}
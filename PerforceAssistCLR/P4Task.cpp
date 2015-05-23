#include "P4Task.h"
#include "STLWrapper.h"

#include "Commands\P4InfoCommand.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace PerforceAssist
{
    P4Task::P4Task() :
        m_p4Task(new VersionControl::P4Task())
    {
    }

    P4Task::~P4Task()
    {
        if(m_p4Task)
        {
            delete m_p4Task;
            m_p4Task = 0;
        }
    }

    bool P4Task::connect(System::String ^user, System::String ^password)
    {
        return m_p4Task->connect(STLWrapper::ToString(user), STLWrapper::ToString(password));
    }

    bool P4Task::disconnect()
    {
        return m_p4Task->disconnect();
    }

    bool P4Task::isConnected()
    {
        return m_p4Task->isConnected();
    }

    System::String^ P4Task::getP4Port()
    {
        return gcnew System::String(m_p4Task->getP4Port().c_str());
    }

    System::String^ P4Task::getP4User()
    {
        return gcnew System::String(m_p4Task->getP4User().c_str());
    }

    System::String^ P4Task::getP4Client()
    {
        return gcnew System::String(m_p4Task->getP4Client().c_str());
    }

    System::String^ P4Task::getP4Password()
    {
        return gcnew System::String(m_p4Task->getP4Password().c_str());
    }

    System::String^ P4Task::getP4Host()
    {
        return gcnew System::String(m_p4Task->getP4Host().c_str());
    }

    System::String^ P4Task::getP4Root()
    {
        return gcnew System::String(m_p4Task->getP4Root().c_str());
    }

    void P4Task::setP4Port(System::String ^port)
    {
        return m_p4Task->setP4Port(STLWrapper::ToString(port));
    }

    void P4Task::setP4User(System::String ^user)
    {
        return m_p4Task->setP4User(STLWrapper::ToString(user));
    }

    void P4Task::setP4Client(System::String ^client)
    {
        return m_p4Task->setP4Client(STLWrapper::ToString(client));
    }

    void P4Task::setP4Password(System::String ^password)
    {
        return m_p4Task->setP4Password(STLWrapper::ToString(password));
    }

    void P4Task::setP4Host(System::String ^host)
    {
        return m_p4Task->setP4Host(STLWrapper::ToString(host));
    }

    void P4Task::setP4Root(System::String ^root)
    {
        return m_p4Task->setP4Root(STLWrapper::ToString(root));
    }
}
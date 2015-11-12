#include "P4Task.hpp"

#include "Commands/P4InfoCommand.hpp"
#include "Commands/P4StatusCommand.hpp"
#include "Commands/P4AddCommand.hpp"
#include "Commands/P4EditCommand.hpp"
#include "Commands/P4NewChangelistCommand.hpp"
#include "Commands/P4ChangesCommand.hpp"
#include "Commands/P4SyncCommand.hpp"
#include "Commands/P4RevertChangesCommand.hpp"
#include "Commands/P4OpenedCommand.hpp"
#include "Commands/P4LockCommand.hpp"
#include "Commands/P4UnlockCommand.hpp"
#include "Commands/P4ClientCommand.hpp"
#include "Commands/P4ClientUpdateCommand.hpp"
#include "Commands/P4DepotCommand.hpp"
#include "Commands/P4ChangelistCommand.hpp"
#include "Commands/P4ChangeUpdateCommand.hpp"
#include "Commands/P4DeleteChangelistCommand.hpp"

#include "Utils/PathUtil.hpp"

#include <string>

using namespace VersionControl;

std::string g_username = "sami";
std::string g_password = "";
std::string g_workspaceName = "TestWorkSpace";
std::string g_port = "localhost:1666";
std::string g_host = "Sami";
std::string g_depotName = "//data/...";
std::string g_depotPath = "//data/...";
std::string g_changelist = "32";
std::string g_workspaceRoot = "";

bool P4TestInfo(P4Task &task)
{
    P4InfoCommand info;
    bool result = task.runCommand(info);
    return result;
}

bool P4TestAdd(P4Task &task)
{
    P4AddCommand add(g_changelist);
    add.AddPath(g_depotPath);
    add.AddCustomArgument("-n");
    bool result = task.runCommand(add);
    return result;
}

bool P4TestEdit(P4Task &task)
{
    P4EditCommand edit(g_changelist);
    edit.AddPath(g_depotPath);
    bool result = task.runCommand(edit);
    return result;
}

bool P4TestNewChangelist(P4Task &task)
{
    P4NewChangelistCommand change(g_workspaceName, g_username, "New change list");
    bool result = task.runCommand(change);
    return result;
}

bool P4TestChanges(P4Task &task)
{
    P4ChangesCommand pending(g_username);
    bool result = task.runCommand(pending);
    return result;
}

bool P4TestSync(P4Task &task)
{
    P4SyncCommand sync;
    sync.AddPath(g_depotPath);
    bool result = task.runCommand(sync);
    return result;
}

bool P4TestOpened(P4Task &task)
{
    P4OpenedCommand opened;
    opened.SetChangelist(g_changelist);
    bool result = task.runCommand(opened);
    return result;
}

bool P4TestRevert(P4Task &task)
{
    P4OpenedCommand opened;
    opened.SetChangelist(g_changelist);

    if(!task.runCommand(opened))
        return false;

    P4RevertChangesCommand revert(false);
    for(auto &tmp : opened.GetOpenedFiles())
    {
        revert.AddPath(tmp.first);
    }
    bool revertResult = task.runCommand(revert);
    return revertResult;
}

bool P4TestLock(P4Task &task)
{
    P4OpenedCommand opened;
    opened.SetChangelist(g_changelist);

    if(!task.runCommand(opened))
    {
        return false;
    }

    P4LockCommand lock;
    for(auto &tmp : opened.GetOpenedFiles())
    {
        lock.AddPath(tmp.first);
    }

    bool result = task.runCommand(lock);
    return result;
}

bool P4TestUnlock(P4Task &task)
{
    P4OpenedCommand opened;
    opened.SetChangelist(g_changelist);
    if(!task.runCommand(opened))
        return false;

    P4UnlockCommand unlock;
    for(auto &tmp : opened.GetOpenedFiles())
    {
        unlock.AddPath(tmp.first);
    }
    bool result = task.runCommand(unlock);
    return result;
}

bool P4TestClient(P4Task &task)
{
    P4ClientCommand client(g_workspaceName);
    bool result = task.runCommand(client);
    return result;
}

bool P4TestClientUpdate(P4Task &task)
{
    P4ClientCommand client(g_workspaceName);
    if(!task.runCommand(client))
        return false;

    P4ClientData data = client.GetClientData();
    data.view.emplace_back("-//data/.../*.zip //TestWorkSpace/data/.../*.zip");

    P4ClientUpdateCommand clientUpdate(data);
    bool result = task.runCommand(clientUpdate);
    return result;
}

bool P4TestDepot(P4Task &task)
{
    P4DepotCommand depot(g_depotName);
    bool result = task.runCommand(depot);
    return result;
}

bool P4TestChangelist(P4Task &task)
{
    P4ChangelistCommand cl(g_changelist);
    bool result = task.runCommand(cl);
    return result;
}

bool P4TestUpdateChangelist(P4Task &task)
{
    P4ChangelistCommand cl(g_changelist);
    if(!task.runCommand(cl))
        return false;

    P4ChangeData clData = cl.GetChangeData();
    clData.description.clear();
    clData.description.emplace_back("Wuuhuu, new changelist desc!");
    clData.description.emplace_back("Second line!");

    P4ChangeUpdateCommand clUpdate(clData);
    bool result = task.runCommand(clUpdate);
    return result;
}

bool P4TestDeleteChangelist(P4Task &task)
{
    P4DeleteChangelistCommand deleteCL(g_changelist);
    bool result = task.runCommand(deleteCL);
    return result;
}

void main()
{
    P4Task task;
    task.setP4Client(g_workspaceName);
    task.setP4Port(g_port);
    task.setP4Host(g_host);

	P4TaskConnectResult result = task.connect(g_username, g_password);

	if (result == P4TaskConnectResult::LoginRequired)
    {
        printf("Failed to connect P4 because login is required!\r\n");
        return;
    }
	else if (result == P4TaskConnectResult::Failed)
	{
		printf("Failed to connect P4!\r\n");
		return;
	}

	printf("Connected to %s successfully!\r\n", g_port.c_str());

    P4TestInfo(task);
    //P4TestAdd(task);
    //P4TestEdit(task);
    //P4TestNewChangelist(task);
    //P4TestChanges(task);
    //P4TestSync(task);
    //P4TestOpened(task);
    //P4TestRevert(task);
    //P4TestLock(task);
    //P4TestUnlock(task);
    //P4TestClient(task);
    //P4TestClientUpdate(task);
    //P4TestDepot(task);

	task.disconnect();
}
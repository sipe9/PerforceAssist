
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
std::string g_workspace = "TestWorkSpace";
//std::string g_host = "localhost:1666";
std::string g_host = "Sami";
std::string g_depot = "data";

void P4Test(P4Task &task)
{
	/*P4InfoCommand info("info");
	task.runCommand(&info, CommandArgs());*/

	/*P4AddCommand add("16");
	add.AddPath("k:/Perforce/TestWorkSpace/data/...");
	task.runCommand(&add, CommandArgs());*/

	/*P4EditCommand edit("16", false);
	//edit.AddPath("k:/Perforce/TestWorkSpace/data/test/...");
	edit.AddPath("//data/...");
	task.runCommand(&edit, CommandArgs());*/

	/*P4NewChangelistCommand change(workspace, username, "New change list");
	task.runCommand(&change, CommandArgs());*/

	/*P4ChangesCommand pending(g_username);
	task.runCommand(&pending, CommandArgs());*/

	/*P4SyncCommand sync;
	sync.AddPath("//data/...");
	task.runCommand(&sync, CommandArgs());*/

	/*P4OpenedCommand opened;
	opened.SetChangelist("29");
	task.runCommand(&opened, CommandArgs());*/

	/*P4RevertChangesCommand revert(false);
	for(auto &tmp : opened.GetOpenedFiles())
	{
		revert.AddPath(tmp.first);
	}
	task.runCommand(&revert, CommandArgs());*/

	//P4LockCommand lock;
	/*for(auto &tmp : opened.GetOpenedFiles())
	{
		lock.AddPath(tmp.first);
	}*/
	//lock.AddPath("//data/test/...");
	//task.runCommand(&lock, CommandArgs());

	//P4UnlockCommand unlock;
	/*for(auto &tmp : opened.GetOpenedFiles())
	{
		unlock.AddPath(tmp.first);
	}*/
	//unlock.AddPath("//data/test/...");
	//task.runCommand(&unlock, CommandArgs());

	/*P4ClientCommand client(g_workspace);
	task.runCommand(&client, CommandArgs());

	P4ClientData data = client.GetClientData();
	data.view.emplace_back("-//data/.../*.zip //TestWorkSpace/data/.../*.zip");

	P4ClientUpdateCommand clientUpdate(data);
	task.runCommand(&clientUpdate, CommandArgs());*/

	/*P4DepotCommand depot(g_depot);
	task.runCommand(&depot, CommandArgs());*/

	/*P4ChangelistCommand cl("default");
	task.runCommand(&cl, CommandArgs());*/

	/*P4ChangeData clData = cl.GetChangeDate();
	clData.description.clear();
	clData.description.emplace_back("Wuuhuu, new changelist desc!");
	clData.description.emplace_back("Second line!");

	P4ChangeUpdateCommand clUpdate(clData);
	task.runCommand(&clUpdate, CommandArgs());*/

	/*P4DeleteChangelistCommand deleteCL("31");
	task.runCommand(&deleteCL, CommandArgs());*/

	/*P4OpenedCommand opened;
	opened.SetChangelist("default");
	task.runCommand(&opened, CommandArgs());*/
}

void main()
{
	P4Task task;
	task.setP4Client(g_workspace);
	task.connect(g_username, g_password, g_host);

	P4Test(task);

	return;
}

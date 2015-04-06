
#include "P4Task.hpp"

#include "Commands/P4InfoCommand.hpp"
#include "Commands/P4StatusCommand.hpp"
#include "Commands/P4AddCommand.hpp"
#include "Commands/P4EditCommand.hpp"
#include "Commands/P4NewChangelistCommand.hpp"
#include "Commands/P4PendingChangelistCommand.hpp"
#include "Commands/P4SyncCommand.hpp"
#include "Commands/P4RevertChangesCommand.hpp"
#include "Commands/P4OpenedCommand.hpp"
#include "Commands/P4LockCommand.hpp"
#include "Commands/P4UnlockCommand.hpp"

#include "Utils/PathUtil.hpp"

#include <string>

using namespace VersionControl;

std::string g_username = "sami";
std::string g_password = "";
std::string g_workspace = "TestWorkSpace";
//std::string g_host = "localhost:1666";
std::string g_host = "Sami";

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

	/*P4NewChangelistCommand change(workspace, username, "New changelist");
	task.runCommand(&change, CommandArgs());*/

	/*P4PendingChangelistCommand pending(g_username);
	task.runCommand(&pending, CommandArgs());*/

	/*P4SyncCommand sync;
	sync.AddPath("//data/...");
	task.runCommand(&sync, CommandArgs());*/

	P4OpenedCommand opened("29", "");
	task.runCommand(&opened, CommandArgs());

	P4RevertChangesCommand revert("29", false);
	for(auto &tmp : opened.GetOpenedFiles())
	{
		revert.AddPath(tmp.first);
	}
	task.runCommand(&revert, CommandArgs());

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
}

void main()
{
	P4Task task;
	task.setP4Client(g_workspace);
	task.connect(g_username, g_password, g_host);

	P4Test(task);

	return;
}

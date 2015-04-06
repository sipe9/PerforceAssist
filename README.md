# PerforceAssist
Perforce Assist wraps common Perforce commands behind simple interface

Fully written in C++ and using standard libraries such as std::string and std::vector. Currently assumes windows as target, shouldn't be an issue to make it work on other platforms.

Using P4 C++ API:
RELEASE = 2015 1;
PATCHLEVEL = 1028542;
SUPPDATE = 2015/03/20;

## How to usage PerforceAssist

First create instance of P4Task, set parameters and connect to P4 with connect();

	P4Task task;
	task.setP4Client("TestWorkSpace");
	task.connect("username", "password", "localhost:1666");
	
Then run commands with task.runCommand();

#### Info
"Display information about the current Perforce application and the shared versioning service."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_info.html

	P4InfoCommand info("info");
	task.runCommand(&info, CommandArgs());

#### Add
"Open file(s) in a client workspace for addition to the depot."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_add.html

	P4AddCommand add("16");
	add.AddPath("k:/Perforce/TestWorkSpace/data/...");
	task.runCommand(&add, CommandArgs());

#### Edit
"Opens file(s) in a client workspace for edit."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_edit.html

	P4EditCommand edit("16", false);
	edit.AddPath("//data/...");
	task.runCommand(&edit, CommandArgs());

#### New changelist
"Create or edit a changelist specification."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_change.html

	P4NewChangelistCommand change("TestWorkSpace", "username", "Description");
	task.runCommand(&change, CommandArgs());

#### Changes
"List submitted and pending changelists."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_changes.html

	P4PendingChangelistCommand pending(g_username);
	task.runCommand(&pending, CommandArgs());

#### Sync
"Update the client workspace to reflect the contents of the depot."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_sync.html

	P4SyncCommand sync;
	sync.AddPath("//data/...");
	task.runCommand(&sync, CommandArgs());

#### List opened files
"List files that are open in pending changelists."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_opened.html

	P4OpenedCommand opened("29", "");
	task.runCommand(&opened, CommandArgs());

#### Revert changes
"Discard changes made to open files."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_revert.html

	P4RevertChangesCommand revert(false);
	task.runCommand(&revert, CommandArgs());

#### Lock
"Lock an opened file against changelist submission."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_lock.html

	P4LockCommand lock;
	lock.AddPath("//data/test/...");
	task.runCommand(&lock, CommandArgs());

#### Unlock
"Release the lock on a file."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_unlock.html

	P4UnlockCommand unlock;
	unlock.AddPath("//data/test/...");
	task.runCommand(&unlock, CommandArgs());
	
## Examples

#### Example of reverting all of the files in specific changelist

This requires two commands, first get list of opened files from changelist and then feed this result to revert command.

	#include "P4Task.hpp"
	#include "Commands/P4OpenedCommand.hpp"
	#include "Commands/P4RevertChangesCommand.hpp"
	
	#include <string>
	
	using namespace VersionControl;
	
	void main()
	{
		// Create P4 tasks, this is used to connect to server and executa commands
		P4Task task;
		
		// Set P4 tasks client
		task.setP4Client("myworkspacename");
		
		// Connect to P4 server
		task.connect("myusername", "mypassword", "localhost:1666");
		
		// Create opened command with changelist number.
		// Second argument is empty, it's for getting all of the opened files from client
		std::string changelist = "29";
		P4OpenedCommand opened(changelist, "");
		
		// Run opened command without additonal arguments
		task.runCommand(&opened, CommandArgs());
		
		P4RevertChangesCommand revert(false);
		
		// Put all of the open files to our revert command
		for(auto &tmp : opened.GetOpenedFiles())
		{
			revert.AddPath(tmp.first);
		}
		
		// Run revert command without additional arguments
		task.runCommand(&revert, CommandArgs());
	}

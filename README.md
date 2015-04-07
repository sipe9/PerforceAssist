# PerforceAssist
Perforce Assist wraps common Perforce commands behind simple interface

Fully written in C++ and using standard libraries such as std::string and std::vector. Currently assumes windows as target, shouldn't be an issue to make it work on other platforms.

Using P4 C++ API:
RELEASE = 2015 1;
PATCHLEVEL = 1028542;
SUPPDATE = 2015/03/20;

## How to use PerforceAssist

First create instance of P4Task, set parameters and connect to P4 with connect();

    P4Task task;
    task.setP4Client(g_workspaceName);
    task.setP4Port(g_port);
    task.setP4Host(g_host);

    if(!task.connect(g_username, g_password))
    {
        printf("Failed to connect P4!\n");
        return;
    }
	
Then run commands with task.runCommand();

#### Info
"Display information about the current Perforce application and the shared versioning service."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_info.html

    P4InfoCommand info;
    bool result = task.runCommand(info);
    return result;

#### Client

##### Get client spec

"Create or edit a client workspace specification and its view."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_client.html

    P4ClientCommand client(g_workspaceName);
    bool result = task.runCommand(client);
    return result;
	
##### Update client spec

    P4ClientCommand client(g_workspaceName);
    if(!task.runCommand(client))
        return false;

    P4ClientData data = client.GetClientData();
    data.view.emplace_back("-//data/.../*.zip //TestWorkSpace/data/.../*.zip");

    P4ClientUpdateCommand clientUpdate(data);
    bool result = task.runCommand(clientUpdate);
    return result;

#### Add
"Open file(s) in a client workspace for addition to the depot."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_add.html

    P4AddCommand add(g_changelist);
    add.AddPath(g_depotPath);
    bool result = task.runCommand(add);
    return result;

#### Edit
"Opens file(s) in a client workspace for edit."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_edit.html

    P4EditCommand edit(g_changelist);
    edit.AddPath(g_depotPath);
    bool result = task.runCommand(edit);
    return result;

#### New changelist
"Create or edit a changelist specification."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_change.html

    P4NewChangelistCommand change(g_workspaceName, g_username, "New change list");
    bool result = task.runCommand(change);
    return result;

#### Changes
"List submitted and pending changelists."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_changes.html

    P4ChangesCommand pending(g_username);
    bool result = task.runCommand(pending);
    return result;

#### Sync
"Update the client workspace to reflect the contents of the depot."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_sync.html

    P4SyncCommand sync;
    sync.AddPath(g_depotPath);
    bool result = task.runCommand(sync);
    return result;

#### List opened files
"List files that are open in pending changelists."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_opened.html

    P4OpenedCommand opened;
    opened.SetChangelist(g_changelist);
    bool result = task.runCommand(opened);
    return result;

#### Revert changes
"Discard changes made to open files."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_revert.html

    P4RevertChangesCommand revert(false);
    revert.AddPath(g_depotPath);
    bool revertResult = task.runCommand(revert);
    return revertResult;

#### Lock
"Lock an opened file against changelist submission."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_lock.html

    P4LockCommand lock;
    revert.AddPath(g_depotPath);
    bool result = task.runCommand(lock);
    return result;

#### Unlock
"Release the lock on a file."

http://www.perforce.com/perforce/r14.2/manuals/cmdref/p4_unlock.html

    P4UnlockCommand unlock;
    revert.AddPath(g_depotPath);
    bool result = task.runCommand(unlock);
    return result;

## Custom arguments
Custom arguments can be added for any command. For example if you want to preview what would happen if you run add command, you'll get the full list of files and what would happen to them without actually modifying any files or metadata.

    P4AddCommand add(g_changelist);
    add.AddPath(g_depotPath);
    add.AddCustomArgument("-n");
    bool result = task.runCommand(add);
    return result;	

## Examples

#### Reverting all of the files in specific changelist

This requires two commands, first get list of opened files from changelist and then feed this result to revert command.

	#include "P4Task.hpp"
	#include "Commands/P4OpenedCommand.hpp"
	#include "Commands/P4RevertChangesCommand.hpp"
	
	#include <string>
	
	using namespace VersionControl;
	
	void main()
	{
	    P4Task task;
	    task.setP4Client(g_workspaceName);
	    task.setP4Port(g_port);
	    task.setP4Host(g_host);
	
	    if(!task.connect(g_username, g_password))
	    {
	        printf("Failed to connect P4!\n");
	        return;
	    }
	
	    P4OpenedCommand opened;
	    opened.SetChangelist(g_changelist);
	
	    if(!task.runCommand(opened))
	        return false;
	
	    P4RevertChangesCommand revert(false);
	    for(auto &tmp : opened.GetOpenedFiles())
	    {
	        revert.AddPath(tmp.first);
	    }
	
	    task.runCommand(revert);
	}

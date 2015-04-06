# PerforceAssist
Perforce Assist wraps common Perforce commands with simple API interface

# How to usage PerforceAssist

First create instance of P4Task, set parameters and connect to P4 with connect();

	P4Task task;
	task.setP4Client("TestWorkSpace");
	task.connect("username", "password", "localhost:1666");
	
Then run commands with task.runCommand();

### Info
	P4InfoCommand info("info");
	task.runCommand(&info, CommandArgs());

### Add
	P4AddCommand add("16");
	add.AddPath("k:/Perforce/TestWorkSpace/data/...");
	task.runCommand(&add, CommandArgs());

### Edit
	P4EditCommand edit("16", false);
	edit.AddPath("//data/...");
	task.runCommand(&edit, CommandArgs());

### New changelist
	P4NewChangelistCommand change(workspace, username, "New changelist");
	task.runCommand(&change, CommandArgs());

### List pending changelists
	P4PendingChangelistCommand pending(g_username);
	task.runCommand(&pending, CommandArgs());

### Sync
	P4SyncCommand sync;
	sync.AddPath("//data/...");
	task.runCommand(&sync, CommandArgs());

### List opened files
	P4OpenedCommand opened("29", "");
	task.runCommand(&opened, CommandArgs());

### Revert changes
	P4RevertChangesCommand revert(false);
	task.runCommand(&revert, CommandArgs());

### Lock
	P4LockCommand lock;
	lock.AddPath("//data/test/...");
	task.runCommand(&lock, CommandArgs());

### Unlock
	P4UnlockCommand unlock;
	unlock.AddPath("//data/test/...");
	task.runCommand(&unlock, CommandArgs());
	
## Combinations

### Revert all of the files in changelist

This requires two commands, first get list of opened files from changelist and then feed this result to revert command.

	P4OpenedCommand opened("29", "");
	task.runCommand(&opened, CommandArgs());
	
	P4RevertChangesCommand revert(false);
	for(auto &tmp : opened.GetOpenedFiles())
	{
		revert.AddPath(tmp.first);
	}
	task.runCommand(&revert, CommandArgs());

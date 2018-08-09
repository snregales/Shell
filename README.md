# Shell
After graduation I realized I dont have mush to show of my current abbilities; so I decided to start this Shell project.
This project is one that was already given to me as a final project in my Operating System course at NMU. But this time around I will be implementing the project with the knowlege that I optain over my time as a student. The idea for this project is to show case my ability so far. These include code redability and documentation, Unit testing, design patterns, pointer manipulation and more.

The aspect of the project is as follow:
<pre>
You may not use the system() command.
YOu may not use the getenv command to get the PATH variable.  You may use it otherwise. 


The Shell Assignment (total 42 points)
	1 Can run an executable
		/bin/ls
	1 You search the path for the executable
		ls
	1 Can do file output redirection "<"
		ls > fred
	1 Can do file input redirection ">"
		cat < fred
	2 Can do command piping "|"
		ls | wc
	+1 Can do lots of pipes
		ls | grep fred | wc
	1 Can do at least one combination of these things
		ls | wc > fred
	4 Can do any combination of three of <, >, and | 
		cat < filename | sort > sortedFile.txt
	2 Can set enviornment variables with your own code
		PATH=:/bin:/sbin:/usr/sbin:/usr/bin
	1 Can set enviornment variables with using putenv/setenv
		PATH=:/bin:/sbin:/usr/sbin:/usr/bin
	2 Expands enviornment variables on the command line
		ls $HOME
	2 Does filename expansion "glob" (Hint:  Use the built in glob.)
		ls a*b
	1 Knows how to change directory
		cd /fred
	1 Bang last command 
		Runs the last command that started with that letter
	        !r runs rm (the last command that started with an 'r')
	1 Bang # command
	        !4 runs 4th command from history
	1 Queue commands
	        make ; make install
	+1 Can have lots of semicolons
		ls; sleep 3; rm fred
	2 Change Prompt
	        PS1="what is you command?"
	3 Can run commands in the background.
		processImage &
	1 Concatenate commands with &.  Only runs next command if the previous 
	  comand returned success.
		cd /home/rappleto & rm fred.txt
	1 Catch Keyboard interrupt
	        ctrl + c = back to prompt
	1 Replace "~" with the home directory
		rm ~/junkfile
	1 Control-L clears the screen
		ctrl-l = clear screen
	3 When they misspell a command, offer a suggestion
		(user) lss
                (shell) Did you mean "ls"?
	2 Can run commands from a file
		. scriptFile.txt
	2 Tab Completion and Arrow History
	1 Saves and reloads history to a file
	2 Aliases work.
		alias dir=ls
	2 Automatically runs a file called .myshell when it starts
	2 Only runs execuatables from an approved list
	1 Prompt has hostname or username.
	-2  Commands cannot have arguments (i.e. ls -l does not work).
</pre>

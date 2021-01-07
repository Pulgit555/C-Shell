# C-Shell
##How To Execute 
-> just type `make`  and then enter `./a.out`.\
##How To Stop 
-> use `ctrl +d` or`quit command`.\

##FILES STRUCTURE 
- makefile      -> used to compile the code\
- headers.h     -> contains all the libraries included useful for different functions\
- main.c        -> includes the main shell loop.\
- prompt.h      -> defines the prompt function.\
- prompt.c      -> prints the shell prompt.\
- input.h       -> defines the input function.\
- input.c       -> takes input, break it into different commands and send it to respective functions.\
- echo.h        -> defines the echo function.\
- echo.c        -> implements the echo command.\
- pwd.h         -> defines the pwd function.\
- pwd.c         -> implements the pwd command.\
- pinfo.h       -> defines the pinfo function.\
- pinfo.c       -> implements the pinfo command.\
- history.h     -> defines the history function.\
- history.c     -> implements the history command.\
- history.txt   -> stores the commands previously used (atmost 20)\
- cd.h          -> defines the cd function.\
- cd.c          -> implements cd command.\
- ls.h          -> defines the ls function.\
- ls.c          -> implements ls command.\
- nightswatch.h -> defines nightswatch function.\
- nightswatch.c -> implements nightswatch command.\
- process.h     -> defines all bgfg function.\
- process.c     -> implements all other commands other than above defined.\
- setenvi.h     -> defines the setenvi function.\
- setenvi.c     -> implements setenv command.\
- unsetenvi.h   -> defines the unsetenvi function.\
- unsetenvi.c   -> implements unsetenv command.\
- jobs.h        -> defines the jobs function.\
- jobs.c        -> implements jobs command.\
- kjob.h        -> defines the kjob function.\
- kjob.c        -> implements kjob command.\
- fg.h          -> defines the fg function.\
- fg.c          -> implements fg command.\
- bg.h          -> defines the bg function.\
- bg.c          -> implements bg command.\
- overkill.h    -> defines the overkill function.\
- overkill.c    -> implements overkill command.\
\
Shell will also implement redirection '>','<','>>' and piping '|' and both.\
Error message is displayed if input file doesnot exist.\
If Output file does not already exist, output file should be created with permissions(0644).\
- overwrite if '>' is used.\
- Append if '>>' is used.\

##Commands Available 
###Built-in Commands 
- cd       -> It will change the working shell directory.\
             command can be used as --`cd ..`,`cd.`,`cd~` and `cd <Directory name>`.\
	     using chdir() system call ,shell changes the current working directory. If in any case, any invalid command is given or a file/directory is not 
	     accessible , it will give respective error.\
	    `cd -` -> It will print the path of previous working directory and changes the current directory to previous working directory.
		if still no directory is changed it will print home directory i.e '~'. \
- pwd      -> It will give the current working directory of shell. command can be used as --`pwd`. using getcwd() system call. if command is incorrect, it will 
             give error.\
- echo     -> It will print whatever is written ahead of it by reducing extra spaces.\
	     command can be used as --`echo (anything you want to write)`.
	     if command is incorrect, it will give error.\
- ls       -> It will give the names of files/directories in that particular directory.\
	 				It can be used as --`ls`,`ls -l`,`ls -a` and `ls -la` along with directory name also(if wanted).\
	 				if the directory name is not mentioned it will consider command for current working directory.\
	 				ls    	--> will list all the files/directory except `.` and `..`\
	 				ls -a   --> will list all the files/directory including `.` and `..`\
	 				ls -l   --> will long-list all the files/directory except `.` and `..`\
	 				ls -al  --> will long-list all the files/directory inlcuding `.` and `..`\
	 				if command is incorrect, it will give error. if the given directory is not available or it cannot access it ,it will give 
					error.\
- setenv   -> It changes the value of environment variable.\
					It can be used as --`setenv var [value]`\
					It changes the environment variable var to value .\
					If number of arguments are wrong it will give error.\
					It will also give error, if it is not able to change the variable.\
- unsetenv   -> It destroys the environment variable.\
					It can be used as --`unsetenv var`\
					It destroys the environment variable var .\
					If number of arguments are wrong it will give error.\
- jobs       -> It will list all currently running background process.\
					It can be used as --`jobs`.\
					It will print process id, process name, pid and its state {Running if status is "R"and "S" and Stopped If status is "T"}\
- kjob       -> It will send signal to a particular signal.\
					It can be used as --`kjob a b`\
					It will send signal corresponding to signal number b to process having process id a.\
					It will print an error if no process with that process id exists.\
- fg         -> It will bring a running or stoppedvbackground process to foreground and changes its state to running.\
					It can be used as --`fg a`\
					It will bring process with process id a to foreground.\
					It will print an error if no process with that process id exists.\
- bg         -> It will change the state of stopped background job to running.\
					It can be used as --`bg a`\
					It will change the state of process with process id a from stopped to running.\
					It will print an error if no process with that process id exists.\
- overkill   -> It will kill all the background processes.\
					It can be used as --`overkill`.\
					
###Other Commands 
- pinfo 		-> It will print the process related info of shell or of particular pid.\
 						It can be used as --`pinfo` and `pinfo <pid>`\
 						It will print pid,process status,memory and executable path.\
 						if command is incorrect, it will give error. if pid is wrong then also it will give error .\ 
 						If no executable path exist ,it will print the other 3 things with error line for executable path.\
- history     -> It will give the latest commands entered in shell.\
 				    	It can be used as --`history` and `history <number>`.\
 				    	It is implemented using history.txt file.\
 				    	history  -> it will print 10(latest commands) if it has stored less than 10 command then it will print that only.\
 				    	history <number> -> it will print maximum of 20 commands only .so when <number> is greater than 20, it will print all the
						stored commands with an error message. and if it has stored less than <number> commands, it will print only the 
						stored commands. if command is incorrect, it will give error.\
- nightswatch -> It can be used as `nightswatch -n <number> interrupt` and `nightswatch -n <number> newborn`.\
 				        It will print after every n seconds.\
 					nightswatch -n <number> interrupt -> print the number of times the CPU(s) has(ve) been interrupted by the keyboard
	controller.using /proc/interrupts file.\ 
 					nightswatch -n <number> newborn   -> print the PID of the process that was most recently created on the system.using "/proc/loadavg file."\ 
						If you want to exit from the command first enter `ctrl + c` then it will ask if you want to quit . if you press q 
						and enter then it will stop immediately and return to shell. else any other input is given and enter is pressed it 
						will keep executing nightswatch command. when it returns to shell it will give two command prompts (maybe because
						of enter after input) if command is incorrect, it will give error.\
	
###others  
-> It can be used as`commandname` and `commandname &`.\
- commandname -> It will run the command in foreground using execvp() system call by first 
 							forking a child and parent will wait till the child process ends.
 							if command is incorrect, execvp will give error.or in case it is not able to fork child 
 							then also it will give error.\
- commandname & -> It will run the command in background using execvp() system call by first
 						 	forking a child , it will not for child to complete rather it provide command prompt and 
 						 	allow to enter more commands.When any background process it will print that command along with exit status 
							and pid. (then you have to press enter to continue).
 						 	Shell will check whether a background process is ended or not by using macros.
 						 	Above defined commands cannot be used as background process.
 						 	It can handle maximum 1000 background process at a time.\
	
###Signals  
- `CTRL-Z` -> It pushes currently running foreground job into the background, and change its state from running to stopped.\
- `CTRL_C` -> It should interrupt any currently running foreground job, by sending it the ​ SIGINT​ signal.\

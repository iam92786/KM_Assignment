
### Q:2 What is difference between fork, vfork and exec system call?


# fork():
* Processes execute the fork() system call to create a new child process.
* The process executing the fork() call is called a parent process. 
* The child process created receives a unique Process Identifier (PID) but retains the parent’s PID as its Parent Process Identifier (PPID).

* ``` getpid(),  getppid()```


# vfork():
* The vfork() system call was first introduced in BSD v3.0. 
* It’s a legacy system call that was originally created as a simpler version of the fork() system call. 
* The child process created by the vfork() system call inherits its parent’s attributes.These include file descriptors, current working directory, signal dispositions, and more.



# exec():
* The exec() system function runs a new process in the context of an existing process and replaces it. 
* This is also referred to as an overlay.
* This system function belongs to a family functions that includes execl(), execlp(), execv(), execvp(), execle(), and execve().


*
###Q:4.Write a list of system calls used in process management with proper syntax?

##System calls Description:

#fork() :
-->To create a new process.
syntax:
       ```pid_t fork(void);```
-->In the syntax the return type is pid_t. 
-->When the child process is successfully created, the PID of the child process is returned in the parent process and 0 
   will be returned to the child process itself.

# exec():
-->The exec() family of functions replaces the current process image with a new process image. 
-->It loads the program into the current process space and runs it from the entry point. 
-->The exec() family consists of following functions,
syntax:
       ```	int execl(const char *path, const char *arg, ...);
       	int execlp(const char *file, const char *arg, ...);
       	int execle(const char *path, const char *arg, ..., 
                                    char * const envp[]);
	       int execv(const char *path, char *const argv[]);
	       int execvp(const char *file, char *const argv[]);
	       int execvpe(const char *file, char *const argv[], 
		                           char *const envp[]);	```


# wait(): 

-->To wait until a created process completes its execution.
syntax:
       ``` pid_t waitpid (child_pid, &status, options);	```

-->The system call wait() is easy. 
-->This function blocks the calling process until one of its child processes exits or a signal is received. 
-->For our purpose, we shall ignore signals. wait() takes the address of an integer variable and returns the process ID 
   of the completed process. 
-->Some flags that indicate the completion status of the child process are passed back with the integer pointer. 
-->One of the main purposes of wait() is to wait for completion of child processes.

-->The execution of wait() could have two possible situations.

   1.If there are at least one child processes running when the call to wait() is made, the caller will be blocked 
     until one of its child processes exits. At that moment, the caller resumes its execution.
   2.If there is no child process running when the call to wait() is made, then this wait() has no effect at all. 
 
# exit(): 
To exit from a process execution.
syntax: 
        ``` void exit ( int status); ``` 

-->The function _exit() terminates the calling process "immediately". 
-->Any open file descriptors belonging to the process are closed; any children of the process are inherited by process 1, 
 * the wait() family of calls.
-->The function _Exit() is equivalent to _exit().

#getpid():

-->Returns the process ID of the parent of the calling process. 
-->If the calling process was created by the fork() function and the parent process still exists at the time of the 
   getppid function call, this function returns the process ID of the parent process. 
-->Otherwise, this function returns a value of 1 which is the process id for init process.
	Syntax:

        ``` pid_t getppid(void);	```

-->Return type: getppid() returns the process ID of the parent of the current process. 
             It never throws any error therefore is always successful.


# getppid(): 
-->To get parent process identifier.
-->returns the process ID of the calling process. 
-->This is often used by routines that generate unique temporary filenames.

Syntax:

	```pid_t getpid(void);	```

-->Return type: getpid() returns the process ID of the current process. 
                It never throws any error therefore is always successful.
# nice():
	To bias the existing priority of a process.


# brk():
	To increase/decrease the data segment size of a process




### Q: 3. How to start a new process in shell? Explain with example how ls command works?



* The shell is a program that takes your commands from the keyboard and gives them to the operating system to perform. 
* A shell hides the details of the underlying operating system and manages the technical details of the operating system kernel interface.
* The prompt, $, which is called command prompt, is issued by the shell. While the prompt is displayed, you can type a command. 
* The shell reads your input after you press Enter. 
* It determines the command you want executed by looking at the first word of your input. 
-->A word is an unbroken set of characters. Spaces and tabs separate words. 
-->Shell script is a list of commands, which are listed in the order of execution.
-->ls is a shell command that lists files and directories within a directory. 
* With the -l option, ls will list out files and directories in long list format.

	a. The shell prompt is displayed

	b. The shell reads the command from standard input that was entered by the user

	c. Parse user input

	d. The shell checks if the first token (the main command itself) is an alias, and if so, replaces the alias with the actual command

	e. Execution




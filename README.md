# Pipex
```diff
- Disclaimer: This is my summary of the Pipex project. 
- The Project Description and High-level Overview are pretty straight-forward and short. 
- The Concepts section works as a digital notebook (sometimes a little messy, my process sketch).
```

## Project Descripton

- Your program will be executed as follows:
```bash
./pipex file1 cmd1 cmd2 file2

$> ./pipex infile "ls -l" "wc -l" outfile
Should behave like: < infile ls -l | wc -l > outfile

$> ./pipex infile "grep a1" "wc -w" outfile
Should behave like: < infile grep a1 | wc -w > outfile
```
- It must take four arguments: file1 and file2 are file names, and cmd1  and cmd2 are shell commands with their parameters.
- You have to turn in a Makefile which will compile your source files. It must not relink.

## High-level Overview

- The program executes <cmd1> with the contents of <infile> as input, and redirects the output to <cmd2>, which writes the result to <outfile>.
- To achieve it, the program creates a pipe using `pipe()` system call. It then forks twice to create two child processes. The first child process `pid1` executes `<cmd1>`, and its output is redirected to the write end of the pipe.
- The second child process `pid2` executes `<cmd2>`, taking the pipe's read end as its input, and writes the result to `<outfile>`. The parent process waits for both child processes to finish before exiting.

| Challenge |  Task  | Short description |
|:-----|:--------:|------:|
| C0   | **`pipe()`** | communicate between processes |

pipe communicate between processes

## Concepts (my digital notebook)
- `perror()` print an error message. It takes a string argument that serves as a prefix to the error message (to the standard error stream). e.g. the prefix `\033[32mError` would set the output color to green;
- `exit()` terminate the program and return an exit status code;
- `EXIT_FAILURE` macro is used as an argument to indicate a general failure (equivalent to `exit(1)`);
- `env` execution environment variables passed to a C program. Each string in the array represents an environment variable in the format `name=value` (info such as: working directory, user-specific settings, system configuration);
- `envp` parameter in the main function. It allows you to access and manipulate the environment variables within your program. You may need to retrieve the value of the `PATH` to determine the directory to search for executables (allowing you to access, modify, and pass them to child processes as needed);
- `PATH` (Unix-like operating systems) contains a list of directories, each one represents a search location for executable files. Otherwise, you will receive a 'command not found' error. Here is how a `PATH` variable might look like:
```
/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
```
- Command Execution: In pipex, you need to execute two commands, cmd1 and cmd2, which are specified by the user as command-line arguments. These commands can be any executable files available in the system. By considering the PATH, you can search for the executables in the directories specified in the PATH variable, allowing the user to provide commands without specifying their full path;
- The PATH variable provides a flexible and convenient way to execute commands without needing to know the exact location of the executable.
- `close()` used to close file descriptors. It takes an integer parameter representing the file descriptor to close;
- `void	close_pipes(t_pipe *pipex)` when you need to pass a structure as its parameter and modify it within the function (the pointer assure precision regarding memory, allowing direct access and modification of its contents). Otherwise, a copy is made and any modifications made to the structure will not affect the original;
- Passing a pointer to the structure allows for more efficient and direct manipulation of the structure's members, avoiding the need to return and assign a modified structure back to the calling code;
- `int pipe(int pipefd[2])` after calling pipe() the array pipefd will contain two file descriptors: `pipefd[0]` for the read end and `pipefd[1]` for the write end. It returns 0 for success and -1 for failure (use errno to determine the specific error);
- `pipe()` is usually used with `fork()` to create a parent-child relationship, where the parent writes data to the pipe, and the child reads the data from the pipe. This allows communication and data sharing between the processes;


- `pid_t fork(void)` if it returns positive, it indicates that the calling process is the parent one and the returned value is the process id(PID) of the newly created child process. If it returns zero, indicates that the calling process is the child one. If it returns negative, an error occurred and the child process was not created;
- It's important to note that after the fork() call, the parent and child processes are independent and can execute different code paths;
- `pid_t` is a data type that represents process Ids(PIDs). It is defined by the `<sys/types.h>` header file. It is a signed integer;
- `pid_t waitpid(pid_t pid, int *status, int options)` `waitpid(pipex.pid1, NULL, 0)` pipex.pid1 specifies the process ID, NULL specifies the address of an integer variable where the exit status of the child process can be stored (NULL means that the parent process is not interested in the exit status of the child). Zero specifies the options for the `waitpid()`, in this case, the parent process will block until the specified child process terminates;
- The purpose of calling `waitpid(pipex.pid1, NULL, 0);` in the given code is to ensure that the parent process waits for the first child process `pipex.pid1` to finish its execution before proceeding further;
- `open()` system call opens the file specified by pathname.  If the specified file does not exist, it may optionally (if `O_CREAT` is specified in flags) be created by `open()`. The return value is a file descriptor, a small, nonnegative integer that is an index to an entry in the process's table of open file descriptors;
- `O_TRUNC` if the file already exists, its contents should be cleared before any data is written to it. This is typically done to ensure that the output file starts with a clean slate. 
- `O_CREAT` this flag is used to create the file if it does not exist.



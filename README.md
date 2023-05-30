# Pipex
```diff
+ keywords: multi-processes programming
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
- It must take four arguments: `file1` and `file2` are file names, and `cmd1` and `cmd2` are shell commands with their parameters.
- You have to turn in a Makefile which will compile your source files. It must not relink.

## High-level Overview

- The program executes `cmd1` with the contents of `infile` as input, and redirects the output to `cmd2`, which writes the result to `outfile`.
- To achieve it, the program creates a pipe using `pipe()` system call. It then forks twice to create two child processes. The first child process `pid1` executes `cmd1`, and its output is redirected to the write end of the pipe.
- The second child process `pid2` executes `cmd2`, taking the pipe's read end as its input, and writes the result to `outfile`. The parent process waits for both child processes to finish before exiting.

1. _Pipe_ -> create first process(parent)
2. _Fork_ -> create first child
3. _Fork_ -> create second child
4. _Parent(main) process_ -> redirect in and out from 2nd to 3rd process
5. **Total:** three processes

```c
int	main(int argc, char* argv[])
{
	int fd[2];
	int pid1;
	int pid2;
	
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0) {
		// first child (ping)
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		// get access to the path environment variable
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	// else is not necessary. after here, code only executed by the parent
	// duplicate fd, both pointing to the same pipe
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0) {
		// child process 2 (grep)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round-trip", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
```

## Summary

- `pipe()` is usually used with `fork()` to create a parent-child relationship, where the parent writes data to the pipe, and the child reads the data from the pipe. This allows communication and data sharing between the processes.

| Task |  Return  | Description | Why |
|:----|:-----:|:--------:|--------:|
| **`fork()`** | `pid_t fork(void)`, id zero if child process, not-zero if main process, negative if error | forking the execution line - parent and child processes in parallel, copy memory over | After its call, the parent and child processes are independent and can execute different code paths |
| **fd** | `fd = 0 (STDIN), fd = 1 (STDOUT), fd = 2 (STDERR), fd = 3 (file.txt)` | unique number across a process | key to a input/output resource, maintained by OS process's table |
| **`pid_t`** | `pid_t fork(void)` | data type, pid stands for process id | x |
| **`pipe()`** | `int pipe(int pipefd[2])`, file descriptor | communicate between processes, 'buffer' that saves memory that you can read(`fd[0]`, STDIN) and write(`fd[1]`, STDOUT) from it |  |
| **`wait()`**  | `waitpid(pipex.pid1, NULL, 0)` | stop the execution until the process is finished. NULL means that the parent process is not interested in the exit status of the child. Zero specifies the options for the `waitpid()`, in this case, the parent process will block until the specified child process terminates | parent process waits for the first child process `pipex.pid1` to finish its execution before proceeding further |
| **`dup()`** | `int dup(int oldfd)`, new file descriptor | duplicates fd | you can have two file descriptors pointing to the same file, but here isn't possible to set the new fd value |
| **`dup2()`** | `int dup2(int oldfd, int newfd)`, new file descriptor. On error, -1 is returned, and errno is set to indicate the error | duplicates fd, allocates a new file descriptor that refers to the same open file description as the descriptor oldfd. So, you can set the new value | if file descriptor newfd was previously open, it is closed before being reused |
|**`PATH`** | x | (Unix-like operating systems) contains a list of directories, each one represents a search location for executable files. Otherwise, you will receive a 'command not found' error `/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin` | flexible and convenient way to execute commands without needing to know the exact location of the executable |
| **`open()`** | `int open(const char *pathname, int flags)`, file descriptor | open and possibly create a file | |
| **`O_TRUNC`** | x | if the file already exists, its contents should be cleared before any data is written to it | ensure that the output file starts with a clean slate | 
| **`O_CREAT`** | x | this flag is used to create the file if it does not exist | |
| **`close()`** | | it takes an integer parameter representing the file descriptor to close | it is standard that you need to close one of the processes of the pipe, e.g.if you write, close the read end and vice-versa |

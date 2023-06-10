# Pipex
```diff
+ keywords: multi-processes programming
+ unidirectional
```
![mind-map_pipex](https://github.com/shinckel/pipex/assets/115558344/85ff3c7a-2594-482f-80b5-7467cf964ce4)

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

1. The parent process calls pipe() to create a pipe and obtains the read and write file descriptors.
2. The parent process calls fork() to create a child process.
3. The child process inherits the file descriptors from the parent.
4. The parent process closes the unnecessary end of the pipe (e.g., the write end if it only needs to read, or the read end if it only needs to write).
5. The child process closes the other end of the pipe.
6. The parent process writes data to the pipe using the write file descriptor.
7. The child process reads data from the pipe using the read file descriptor.

### Why there are three proccesses?

1. Parent Process: The parent process is responsible for setting up the input and output redirection and coordinating the execution of the child processes. It creates the pipe to establish communication channels between the processes.
2. First Child Process: The first child process is created by forking the parent process. Its purpose is to execute the first command specified in the command line and redirect its output to the second child process.
3. Second Child Process: The second child process is also created by forking the parent process. Its purpose is to execute the second command specified in the command line and receive input from the first child process.

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

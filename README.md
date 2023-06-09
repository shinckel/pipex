# Pipex
This project is initiated by 42 school. For comprehensive information regarding the requirements, please consult the PDF file in the subject folder of the repository. Furthermore, I have provided my notes and a concise summary below.
```diff
+ keywords: multi-processes programming
+ unidirectional
```
Mindmap about the project structure (shinckel, 2023)
![mind-map_pipex](https://github.com/shinckel/pipex/assets/115558344/85ff3c7a-2594-482f-80b5-7467cf964ce4)

## High-level Overview

- The program will be executed as follows:
```bash
./pipex file1 cmd1 cmd2 file2

$> ./pipex infile "ls -l" "wc -l" outfile
Should behave like: < infile ls -l | wc -l > outfile

$> ./pipex infile "grep a1" "wc -w" outfile
Should behave like: < infile grep a1 | wc -w > outfile
```
- It must take four arguments: `file1` and `file2` are file names, and `cmd1` and `cmd2` are shell commands with their parameters.
- The program executes `cmd1` with the contents of `infile` as input, and redirects the output to `cmd2`, which writes the result to `outfile`.
- Parent Process: The parent process is responsible for setting up the input and output redirection and coordinating the execution of the child processes. It creates the pipe to establish communication channels between the processes.

1. The parent process calls pipe() to create a pipe and obtains the read and write file descriptors;
2. The parent process calls fork() to create two children;
3. The children inherits the file descriptors from the parent;
4. The children close the unnecessary end of the pipe (e.g., the write end if it only needs to read, or the read end if it only needs to write);
5. First child process `pid1` executes `cmd1` with the contents of `infile` as input and writes data to the pipe using the write file descriptor;
6. Second child process `pid2` executes `cmd2`, taking the pipe's read end as its input, and writes the result to `outfile`;
7. The parent process waits for both child processes to finish before exiting.

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

## Concepts

| Task |  Return  | Description |
|:----|:-----:|:--------:|
| **`fork()`** | `pid_t fork(void)`, id zero if child process, not-zero if main process, negative if error | Forking the execution line - parent and child processes in parallel, copy memory over. After its call, the parent and child processes are independent and can execute different code paths |
| **fd** | `fd = 0 (STDIN), fd = 1 (STDOUT), fd = 2 (STDERR), fd = 3 (file.txt)` | Unique number across a process. Key to a input/output resource, maintained by OS process's table |
| **`pid_t`** | `pid_t fork(void)` | Data type, pid stands for process id |
| **`pipe()`** | `int pipe(int pipefd[2])`, file descriptor | Communicate between processes, 'buffer' that saves memory that you can read(`fd[0]`, STDIN) and write(`fd[1]`, STDOUT) from it |
| **`exit()`** | `noreturn void exit(int status)` | cause normal process termination(and return control to the operating system). exit(1) is used to terminate the program with an error status, while return is used to exit from a function and provide a return value. The status can be EXIT_SUCCESS(0) or EXIT_FAILURE(1) |
| **`wait()`**  | `waitpid(pipex.pid1, NULL, 0)` | Stop the execution until the process is finished. NULL means that the parent process is not interested in the exit status of the child. Zero specifies the options for the `waitpid()`, in this case, the parent process will block until the specified child process terminates. Parent process waits for the first child process `pipex.pid1` to finish its execution before proceeding further |
| **`dup()`** | `int dup(int oldfd)`, new file descriptor | Duplicates fd. You can have two fd pointing to the same file, but here isn't possible to set the new fd value |
| **`dup2()`** | `int dup2(int oldfd, int newfd)`, new file descriptor. On error, -1 is returned, and `errno` is set to indicate the error | Duplicates fd, allocates a new file descriptor that refers to the same open file description as the descriptor oldfd. So, you can set the new value. If file descriptor `newfd` was previously open, it is closed before being reused |
|**`PATH`** | `echo $PATH` `which ls` | (Unix-like operating systems) contains a list of directories, each one represents a search location for executable files. Otherwise, you will receive a 'command not found' error `/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin`. Flexible and convenient way to execute commands without needing to know the exact location of the executable |
| **`open()`** | `int open(const char *pathname, int flags)`, file descriptor | open and possibly create a file |
| **`O_TRUNC`** | x | if the file already exists, its contents should be cleared before any data is written to it. Ensure that the output file starts with a clean slate | 
| **`O_CREAT`** | x | this flag is used to create the file if it does not exist |
| **`close()`** | | it takes an integer parameter representing the file descriptor to close. It is standard that you need to close one of the processes of the pipe, e.g.if you write, close the read end and vice-versa |
| **`address()`** | `int access(const char *pathname, int mode)`, On success (all requested permissions granted, or mode is F_OK and the file exists), zero is returned. Otherwise, -1 is returned | it checks whether the calling process can access the file pathname, F_OK tests for the existence of the file. R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively |
| **`execlp()`** | `int execlp(const char *file, const char *arg, ...)`, only return if an error has occurred(-1) | initial argument is the name of a file that is to be executed, subsequent ellipses(arg0, arg1, ..., argn). Together they describe a list of one or more pointers to null-terminated strings that represent the argument list available to the executed program. NULL terminated. The file is sought in the colon-separated list of directory pathnames specified in the PATH environment variable |
| **`execve()`** | `int execve(const char *pathname, char *const argv[], char *const envp[])` | 
| **`struct`** | `typedef struct` | Declare a new datatype of your own, unify several variables of different datatypes into a single, new variable. dot notation (.) is used to access members of a struct when you have an actual instance of the struct, whereas the arrow notation (->) is used to access members of a struct when you have a pointer to the struct |
| **`linked list`** | `typedef struct node {int number; struct node *next;} node;` | more dynamic data structure, you can expand or shrink it, as it is spread out in computer memory (it doesn't have contiguous memory as arrays). However, how to find it? Every number that I care about will have metadata(pointer to the next element). Last node will be NULL(absence of an address, 0x0). Plot it anywhere! Where there is room. Nodes connected via pointers (the tradeoff is: it uses more memory) |
| **`fsanitize`** | `-fsanitize=address -g ` | When you compile your code with the -g flag, the compiler includes information such as variable names, line numbers, and function names in the generated binary. This allows debugging tools like debuggers to map the compiled code back to the original source code, making it easier to analyze and debug the program. Check sanitizer support: Run the command `clang --help | grep sanitize` in your terminal to see if the sanitizer options are listed |
| **`lldb`** | Run -> `lldb ./pipex` `run grocery_list.txt "head -4" "cat" sorted3.txt` | interactive debugger tool (attach events/errors to the program), explore source code. To enable debugging symbols with LLDB, you need to compile your program with the -g flag. This flag tells the compiler (e.g. gcc or clang) to include debug information in the executable file. Relunch -> `target create ./pipex` |
| **`breakpoint, backtrace, graphical-user-interface`** | `b` `bt` `gui`||
| **`valgrind`** |

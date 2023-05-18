# Pipex

## Mandatory Part

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

## High-level overview

- The program executes <cmd1> with the contents of <infile> as input, and redirects the output to <cmd2>, which writes the result to <outfile>.
- To achieve it, the program creates a pipe using `pipe()` system call. It then forks twice to create two child processes. The first child process (`pid1`) executes `<cmd1>`, and its output is redirected to the write end of the pipe.
- The second child process (`pid2`) executes `<cmd2>`, taking the pipe's read end as its input, and writes the result to `<outfile>`. The parent process waits for both child processes to finish before exiting.


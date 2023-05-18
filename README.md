# Pipex

## Project descripton

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
- To achieve it, the program creates a pipe using `pipe()` system call. It then forks twice to create two child processes. The first child process `pid1` executes `<cmd1>`, and its output is redirected to the write end of the pipe.
- The second child process `pid2` executes `<cmd2>`, taking the pipe's read end as its input, and writes the result to `<outfile>`. The parent process waits for both child processes to finish before exiting.

## Detailed

1. Check if it received correct number of command-line arguments;
2. Create a pipe `pipe()`. It has two file descriptors: `pipefd[0]` for the read end, and `pipefd[1]` for the write end;
3. Fork the first child process `pid1`
4. Inside the first child process:
- Close the read end of the pipe `pipefd[0]`
- Redirect the standard output `STDOUT_FILENO` to the write end of the pipe `pipefd[1]`
- Close the write end of the pipe `pipefd[1]` (it is only using the read end)
- Open the input file `<infile>` in read-only mode
- Redirect the standard input `STDIN_FILENO` to the input file
- Execute `cmd1` using the `execlp()` function
6. Fork the second child process `pid2`
7. Inside the second child process:
- 


## Functions
- `perror()` print an error message. It takes a string argument that serves as a prefix to the error message (to the standard error stream). e.g. the prefix `\033[32mError` would set the output color to green;
- `exit()` terminate the program and return an exit status code;
- `EXIT_FAILURE` macro is used as an argument to indicate a general failure (equivalent to `exit(1)`);

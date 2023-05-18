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

## My structure


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:02:13 by shinckel          #+#    #+#             */
/*   Updated: 2023/05/30 20:23:23 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_pipex.h"

// first child
first_child(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);

	execve(pipex->cmd, pipex->cmd_args, envp);
}

// second child
second_child(char **argv, char **envp, t_pipex *pipex)
{

}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// *envp + 5 skips the "PATH=" prefix and works just as getenv()
char	*find_path(char **envp, t_pipex *pipex, char *cmd)
{
	char	*tmp;
	char	*command;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->cmd_paths = ft_split(*envp + 5, ':');
	while (cmd)
	{
		tmp = ft_strjoin(pipex->cmd_paths, '/');
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		pipex->cmd_paths++;
	}
	return (NULL);
}

/* fd[0] read end, fd[1] write end, no further communication can occur...
therefore, no leaks associated to the pipe */
/* the argument must be pipex adresss(&pipex) for changing original */
void	close_pipes(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	create_pipe(char **argv, char **envp, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		msg_error(ERR_INFILE);
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile < 0)
		msg_error(ERR_OUTFILE);
	if (pipe(pipex->fd) < 0)
		msg_error(ERR_PIPE);
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		first_child(argv, envp, pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		second_child(argv, envp, pipex);
	close_pipes(&pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.outfile = dup(STDOUT_FILENO);
	if (argc == 5 && envp[0] != NULL)
		creat_pipe(argv, envp, &pipex);
	else
	{
		write(pipex.outfile, ERR_INPUT, ft_strlen(ERR_INPUT));
		exit(1);
	}
	return (0);
}

/* Child process - run inside a fork, take the filein, put output inside a pipe and then close with the exec function */

/* Parent process - take the data from the pipe, change the output for the 
fileout and also close with the exec funcion */

/* Run program - main function that run the child and parent process or display an error message if arguments are wrong */
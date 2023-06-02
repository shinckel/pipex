/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:02:13 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/01 21:26:15 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_pipex.h"

// first child
void	first_child(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	dup2(pipex->infile, STDIN_FILENO);
	pipex->cmd_args = ft_split(argv[2], ' ');
	pipex->cmd = find_path(envp, pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		child_free(pipex);
		msg_error(ERR_CMD);
		exit(1);
	}
	execve(pipex->cmd, pipex->cmd_args, envp);
}

// second child
void	second_child(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	dup2(pipex->outfile, STDOUT_FILENO);
	pipex->cmd_args = ft_split(argv[3], ' ');
	pipex->cmd = find_path(envp, pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		child_free(pipex);
		msg_error(ERR_CMD);
		exit(1);
	}
	execve(pipex->cmd, pipex->cmd_args, envp);
}

// *envp + 5 skips the "PATH=" prefix and works just as getenv()
char	*find_path(char **envp, t_pipex *pipex, char *cmd)
{
	char	*tmp;
	char	*command;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->cmd_paths = ft_split(*envp + 5, ':');
	while (pipex->cmd_paths)
	{
		tmp = ft_strjoin(*pipex->cmd_paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK | F_OK) == 0)
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
	close_pipes(pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	parent_free(pipex);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	//pipex.outfile = dup(STDOUT_FILENO);
	if (argc == 5 && envp[0] != NULL)
		create_pipe(argv, envp, &pipex);
	else
	{
		write(pipex.outfile, ERR_INPUT, ft_strlen(ERR_INPUT));
		exit(1);
	}
	return (0);
}

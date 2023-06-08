/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:02:13 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/08 17:18:36 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// first child
// exit with the right status...
// dup2 is closing infile here... but is missing outfile
void	first_child(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->outfile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	pipex->cmd = find_path(envp, pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		child_free(pipex);
		msg_error(ERR_1CMD);
	}
	exit(execve(pipex->cmd, pipex->cmd_args, envp));
}

// second child
void	second_child(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->infile);
	pipex->cmd_args = ft_split(argv[3], ' ');
	pipex->cmd = find_path(envp, pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		child_free(pipex);
		msg_error(ERR_2CMD);
	}
	exit(execve(pipex->cmd, pipex->cmd_args, envp));
}

// *envp + 5 skips the "PATH=" prefix and works just as getenv()
char	*find_path(char **envp, t_pipex *pipex, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->cmd_paths = ft_split(*envp + 5, ':');
	while (*pipex->cmd_paths != NULL)
	{
		tmp = ft_strjoin(*pipex->cmd_paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		free(command);
		pipex->cmd_paths++;
	}
	while (*pipex->cmd_paths)
		free(*pipex->cmd_paths++);
	return (NULL);
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
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pid1, &pipex->status1, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
	close(pipex->infile);
	close(pipex->outfile);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.message = dup(STDERR_FILENO);
	if (argc == 5 && envp[0] != NULL)
	{
		create_pipe(argv, envp, &pipex);
		if (WEXITSTATUS(pipex.status1) == 0 && WEXITSTATUS(pipex.status2) == 0)
			write(pipex.message, SUCESS, ft_strlen(SUCESS));
	}
	else
	{
		write(pipex.message, ERR_INPUT, ft_strlen(ERR_INPUT));
		exit(EXIT_FAILURE);
	}
	return (0);
}

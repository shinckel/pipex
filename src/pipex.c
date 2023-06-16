/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:02:13 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/16 20:16:33 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// first child
// exit with the right status...
void	first_child(char **argv, char **envp, t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->dup1[0] = dup2(pipex->fd[1], STDOUT_FILENO);
	close_fds(pipex->fd[0], pipex->fd[1]);
	pipex->dup1[1] = dup2(pipex->infile, STDIN_FILENO);
	close_fds(pipex->infile, pipex->outfile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	pipex->cmd = find_path(envp, pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		while (pipex->cmd_args[++i])
			free(pipex->cmd_args[i]);
		free(pipex->cmd_args);
		close_fds(pipex->dup1[0], pipex->dup1[1]);
		msg_error(ERR_1CMD, pipex->flag);
	}
	exit(execve(pipex->cmd, pipex->cmd_args, envp));
}

// second child
void	second_child(char **argv, char **envp, t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->dup2[0] = dup2(pipex->fd[0], STDIN_FILENO);
	close_fds(pipex->fd[0], pipex->fd[1]);
	pipex->dup2[1] = dup2(pipex->outfile, STDOUT_FILENO);
	close_fds(pipex->infile, pipex->outfile);
	pipex->cmd_args = ft_split(argv[3], ' ');
	pipex->cmd = find_path(envp, pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		while (pipex->cmd_args[++i])
			free(pipex->cmd_args[i]);
		free(pipex->cmd_args);
		close_fds(pipex->dup2[0], pipex->dup2[1]);
		msg_error(ERR_2CMD, pipex->flag);
	}
	exit(execve(pipex->cmd, pipex->cmd_args, envp));
}

// *envp + 5 skips the "PATH=" prefix and works just as getenv()
char	*find_path(char **envp, t_pipex *pipex, char *cmd)
{
	int	i;

	i = -1;
	if (!cmd || string_empty(cmd))
	{
		pipex->flag = 1;
		return (NULL);
	}
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->cmd_paths = ft_split(*envp + 5, ':');
	while (pipex->cmd_paths[++i] != NULL)
	{
		pipex->tmp = ft_strjoin(pipex->cmd_paths[i], "/");
		pipex->command = ft_strjoin(pipex->tmp, cmd);
		free(pipex->tmp);
		if (access(pipex->command, X_OK | F_OK) == 0)
			return (pipex->command);
		free(pipex->command);
	}
	free_paths(pipex);
	return (NULL);
}

int	create_pipe(char **argv, char **envp, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		msg_error(ERR_INFILE, pipex->flag);
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile < 0)
		msg_error(ERR_OUTFILE, pipex->flag);
	if (pipe(pipex->fd) < 0)
		msg_error(ERR_PIPE, pipex->flag);
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		first_child(argv, envp, pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		second_child(argv, envp, pipex);
	close_fds(pipex->fd[0], pipex->fd[1]);
	close_fds(pipex->infile, pipex->outfile);
	waitpid(pipex->pid1, &pipex->status1, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.flag = 0;
	if (argc == 5 && envp[0] != NULL)
	{
		create_pipe(argv, envp, &pipex);
		if (WEXITSTATUS(pipex.status1) == 0 && WEXITSTATUS(pipex.status2) == 0)
			write(1, SUCCESS, ft_strlen(SUCCESS));
	}
	else
	{
		write(1, ERR_INPUT, ft_strlen(ERR_INPUT));
		exit(EXIT_FAILURE);
	}
	return (0);
}

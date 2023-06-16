/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:34:00 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/16 13:12:18 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_error(char *err, t_pipex *pipex)
{
	if (pipex->flag == 1)
	{
		errno = 1;
		perror(err);
	}
	else
		perror(err);
	exit (EXIT_FAILURE);
}

void	free_paths(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->cmd_paths[++i])
		free(pipex->cmd_paths[i]);
	free(pipex->cmd_paths);
}

void	close_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:34:00 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/14 19:40:12 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// errors
void	msg_error(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

void	cmd_free(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i++])
		free(cmd[i]);
	free(cmd);
}

void	close_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

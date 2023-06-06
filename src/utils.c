/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:34:00 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/06 21:32:43 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_pipex.h"

// errors
void	msg_error(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

// free (manage leaks)
void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	// free(pipex->cmd_args);
	free(pipex->cmd);
}

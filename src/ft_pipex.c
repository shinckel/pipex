/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:02:13 by shinckel          #+#    #+#             */
/*   Updated: 2023/05/18 18:50:47 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

/* Child process - run inside a fork, take the filein, put output inside a pipe
and then close with the exec function */

/* Parent process - take the data from the pipe, change the output for the 
fileout and also close with the exec funcion */

/* Run program - main function that run the child and parent process or display 
an error message if arguments are wrong */
int	main(int argc, char *argv)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
	}
	else 
	{
		fd_putstr_fd("")
	}
	return (0);
}
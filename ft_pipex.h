/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:30:15 by shinckel          #+#    #+#             */
/*   Updated: 2023/01/30 16:23:21 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
/*write, close, pipe, access*/
# include <unistd.h>
/*open, */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
/*malloc, free*/
# include <stdlib.h>
/*strerror, perror*/
# include <stdio.h>
# include <errno.h>


#endif
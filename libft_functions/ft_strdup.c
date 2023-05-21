/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:20:58 by shinckel          #+#    #+#             */
/*   Updated: 2023/05/21 17:24:52 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	char	*aux;
	int		len;

	len = ft_strlen(s) + 1;
	copy = (char *)malloc(sizeof(char) * len);
	if (copy == NULL)
		return (0);
	aux = copy;
	while (*s)
	{
		*aux = *s;
		aux++;
		s++;
	}
	*aux = '\0';
	return (copy);
}

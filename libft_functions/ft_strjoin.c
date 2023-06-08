/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:22:04 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/08 15:19:35 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*aux;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	len = i + j;
	aux = (char *)malloc(sizeof(char) * (len + 1));
	if (!aux)
		return (NULL);
	ft_memmove(aux, s1, i);
	ft_memmove(aux + i, s2, j);
	aux[len] = '\0';
	return (aux);
}

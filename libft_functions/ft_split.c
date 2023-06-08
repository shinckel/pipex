/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:36 by shinckel          #+#    #+#             */
/*   Updated: 2023/06/08 15:19:27 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	word_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
			if (s[i] == '\0')
				return (words);
		}
		i++;
	}
	return (words);
}

// as you are using malloc to allocate memory, it needs to be freed after usage
// in this project, cmd_paths and cmd_args!
char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;
	unsigned int	end;
	char			**aux;

	end = word_count(s, c);
	aux = (char **)malloc((end + 1) * sizeof(char *));
	if (!aux)
		return (NULL);
	start = 0;
	j = 0;
	while (start < end)
	{
		i = 0;
		while (s[j] != '\0' && s[j] == c)
			j++;
		while (s[j + i] != c && s[j + i] != '\0')
			i++;
		aux[start] = ft_substr(s, j, i);
		start++;
		j += i;
	}
	aux[end] = NULL;
	return (aux);
}

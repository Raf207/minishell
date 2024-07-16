/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:27:58 by rafnasci          #+#    #+#             */
/*   Updated: 2024/07/08 18:59:44 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issep(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
		if (c == sep[i])
			return (1);
	return (0);
}

static int	ft_wordcount(char const *s, char *sep)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		while (ft_issep(s[i], sep) && s[i])
			i++;
		if (s[i])
		{
			wordcount++;
			while (!ft_issep(s[i], sep) && s[i])
			{
				i++;
			}
		}
	}
	return (wordcount);
}

static void	ft_free(char **rep)
{
	int	i;

	i = 0;
	while (rep[i] != NULL)
	{
		free(rep[i]);
		i++;
	}
	free(rep);
}

static char	*ft_lettercount(char const *s, char *sep, char **rep, int word)
{
	int	i;
	int	len;

	i = 0;
	while (!ft_issep(s[i], sep) && s[i])
		i++;
	rep[word] = ft_calloc(i + 1, sizeof(char));
	if (!rep[word])
	{
		ft_free(rep);
		return (NULL);
	}
	len = 0;
	while (len < i)
	{
		rep[word][len] = s[len];
		len++;
	}
	return (rep[word]);
}

char	**ft_split(char const *s, char *sep)
{
	int		wordcount;
	int		i;
	char	**rep;

	if (!s)
		return (NULL);
	wordcount = 0;
	i = 0;
	(rep) = ft_calloc(ft_wordcount(s, sep) + 1, sizeof(char *));
	if (!(rep))
		return (NULL);
	while (s[i])
	{
		while (ft_issep(s[i], sep) && s[i])
			i++;
		if (s[i])
		{
			if (!ft_lettercount(&s[i], sep, (rep), wordcount))
				return (NULL);
			while (s[i] && !ft_issep(s[i], sep))
				i++;
			wordcount++;
		}
	}
	return ((rep));
}

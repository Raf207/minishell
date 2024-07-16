/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:29:54 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/14 18:57:37 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *) s1);
	if (n == 0)
		return (NULL);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] && s2[j] == s1[i + j] && (i + j) < n)
		{
			if (s2[j + 1] == '\0')
				return ((char *) &s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

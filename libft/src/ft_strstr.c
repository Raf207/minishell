/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:02:49 by rafnasci          #+#    #+#             */
/*   Updated: 2024/01/22 12:03:23 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *) s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] && s2[j] == s1[i + j])
		{
			if (s2[j + 1] == '\0')
				return ((char *) &s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

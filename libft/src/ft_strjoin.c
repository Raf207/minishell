/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:25:54 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/17 17:19:54 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rep;
	int		tot_len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	tot_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	rep = (char *) malloc (sizeof(char) * tot_len);
	if (!rep)
		return (NULL);
	tot_len = 0;
	while (s1[tot_len])
	{
		rep[tot_len] = s1[tot_len];
		tot_len++;
	}
	i = 0;
	while (s2[i])
	{
		rep[tot_len] = s2[i];
		i++;
		tot_len++;
	}
	rep[tot_len] = '\0';
	return (rep);
}

// #include <stdio.h>
// int main (void)
// {
// 	char s1[] = "bonjour";
// 	char *s2 = NULL;
// 	printf("%s\n", ft_strjoin(s1, s2));
// }

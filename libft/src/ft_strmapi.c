/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:17:02 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/17 17:16:27 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rep;

	i = 0;
	if (!s || !f)
		return (NULL);
	rep = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!rep)
		return (NULL);
	while (s[i])
	{
		rep[i] = (*f)(i, s[i]);
		i++;
	}
	return (rep);
}

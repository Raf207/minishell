/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:02:43 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/30 15:31:41 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*src;
	size_t		i;

	if (n == 0)
		return (NULL);
	src = (const char *) s;
	i = 0;
	while (i < n - 1 && src[i] != (const char) c)
		i++;
	if (src[i] == (char) c)
		return ((char *) &src[i]);
	else
		return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:20:38 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/14 15:28:57 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*src1;
	const char	*src2;
	size_t		i;

	src1 = (const char *) s1;
	src2 = (const char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (src1[i] == src2[i] && i < n - 1)
		i++;
	return ((unsigned char) src1[i] - (unsigned char) src2[i]);
}

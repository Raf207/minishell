/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:42:50 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/16 17:51:28 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)s;
	i = -1;
	while (++i < n)
		src[i] = c;
	return (s);
}

// int main(void)
// {
// 	int tab[5] = {0,1,2,3,4};
// 	int tab2[5] = {0,1,2,3,4};
// 	int i = 0;
// 	ft_memset(tab, 0, sizeof(int) * 5);
// 	memset(tab2, 0, sizeof(int) * 5);
// 	while (i < 5)
// 	{
// 		printf("%d = ", tab2[i]);
// 		printf("%d\n", tab[i]);
// 		i++;
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:51:48 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/16 15:30:20 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		d_len;

	i = -1;
	d_len = ft_strlen(dst);
	if (size == 0 || size <= d_len)
		return (ft_strlen(src) + size);
	while ((++i + d_len) < (size - 1) && src[i])
		dst[d_len + i] = src[i];
	dst[d_len + i] = '\0';
	return (ft_strlen(src) + d_len);
}

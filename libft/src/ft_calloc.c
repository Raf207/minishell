/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:17:40 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/18 14:35:44 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rep;
	size_t	total;

	total = count * size;
	if (size && total / size != count)
		return (NULL);
	rep = malloc(count * size);
	if (!rep)
		return (NULL);
	ft_memset(rep, 0, count * size);
	return (rep);
}

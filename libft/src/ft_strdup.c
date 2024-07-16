/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:33:10 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/14 17:05:51 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;

	dst = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, ft_strlen(s) + 1);
	return (dst);
}

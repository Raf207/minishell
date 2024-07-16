/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:27:07 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/30 15:53:48 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_countdigit(long n)
{
	int	i;

	if (n <= 0)
	{
		i = 1;
		n *= -1;
	}
	else
		i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_invert(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str);
	if (str[i] == '-')
		i++;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*rep;
	int		digits;
	long	nb;

	nb = n;
	rep = ft_calloc(ft_countdigit(nb) + 1, sizeof(char));
	if (!rep)
		return (NULL);
	digits = 0;
	if (nb < 0)
	{
		rep[digits] = '-';
		digits++;
		nb *= -1;
	}
	rep[digits] = '0';
	while (nb > 0)
	{
		rep[digits] = (nb % 10) + '0';
		nb = nb / 10;
		digits++;
	}
	return (ft_invert(rep));
}

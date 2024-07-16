/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:05:55 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/27 15:14:00 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ');
}

static int	ft_ignorespace(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

static int	ft_sign(const char *str, int *i)
{
	int	neg;

	neg = 1;
	if (str[(*i)] == '+' || str[(*i)] == '-')
	{
		if (str[(*i)] == '-')
			neg *= -1;
		(*i)++;
	}
	return (neg);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long long	rep;
	long long	temp;

	rep = 0;
	i = ft_ignorespace(str);
	neg = ft_sign(str, &i);
	temp = (rep * 10) + (str[i] - '0');
	while (ft_isdigit(str[i]))
	{
		rep = (rep * 10) + (str[i] - '0');
		if (rep < temp && temp * neg < 0)
			return (0);
		else if (rep < temp && temp * neg > 0)
			return (-1);
		temp = rep;
		i++;
	}
	return (rep * neg);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char rep[] = "15465166518131613513516561351";
// 	(void) rep;
// 	printf("%d = %d\n", ft_atoi(rep), atoi(rep));
// }
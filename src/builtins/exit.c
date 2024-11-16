/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:51:17 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/16 15:11:39 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exit(char *arg, long n)
{
	if (arg)
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", arg);
		exit(g_exitcode = 255);
	}
	else
	{
		ft_printf_fd(1, "exit\n");
		exit(g_exitcode = n % 256);
	}
}

static long	ft_atol(const char *str, int *overflow)
{
	int		i;
	int		sign;
	long	num;
	long	buf;

	i = 0;
	sign = 1;
	num = 0;
	buf = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9' && !*overflow)
	{
		num = (num * 10) + (str[i++] - 48) * sign;
		if ((buf > num && sign > 0) || (buf < num && sign < 0))
			*overflow = 1;
		buf = num;
	}
	if ((str[i] && (str[i] < 9 || str[i] > 13 || (str[i] != 32))))
		*overflow = 1;
	return (num);
}

void	exit_built(char **token)
{
	char	*arg;
	long	n;
	int		overflow;

	if (!token[1])
	{
		ft_printf_fd(1, "exit\n");
		exit(g_exitcode);
	}
	arg = ft_strdup(token[1]);
	overflow = 0;
	n = ft_atol(arg, &overflow);
	if (overflow)
		ft_exit(arg, n);
	if (token[2])
	{
		ft_printf_fd(2, "bash: exit: too many arguments\n");
		g_exitcode = 1;
	}
	else
		ft_exit(NULL, n);
	free(arg);
}
// FREE ALL
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:51:17 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/21 14:49:44 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		num = (num * 10 + (str[i++] - 48)) * sign;
		if ((buf > num && sign > 0) || (buf < num && sign < 0))
			*overflow = 1;
		buf = num;
	}
	if ((str[i] && (str[i] < 9 || str[i] > 13 || (str[i] != 32))))
		*overflow = 1;
	return (num);
}

void	exit_built(t_token_list *token)
{
	char	*arg;
	long	n;
	int		overflow;

	arg = token->next->value;
	overflow = 0;
	n = ft_atol(arg, &overflow);
	//printf("n : %ld\n", n);
	if (overflow)
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", arg);
		g_exitcode = 255;
		exit(g_exitcode);
	}
	if (token->next->next->value)
		ft_printf_fd(2, "bash: exit: too many arguments\n");
	else
	{
		g_exitcode = n % 256;
		//printf("g_code : %d\n", g_exitcode);
		exit(g_exitcode);
	}
}
// FREE ALL
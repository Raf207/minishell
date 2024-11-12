/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:40:16 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/12 16:20:45 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_nl(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	echo_built(char **token)
{
	int	count;
	int	i;
	int	nl;

	count = 1;
	i = 1;
	nl = 1;
	while (token[count])
		count++;
	while (token[i] && !check_nl(token[i]))
	{
		i++;
		nl = 0;
	}
	while (token[i])
	{
		ft_printf_fd(1, "%s", token[i]);
		if (i != count -1)
			write(1, " ", 2);
		i++;
	}
	if (nl)
		printf("\n");
}

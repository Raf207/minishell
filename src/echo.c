/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:40:16 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/12 02:34:32 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		++i;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

static void	write_echo(int count, int i, bool new_line, char **args)
{
	while (args[i] && check_new_line(args[i]))
	{
		++i;
		new_line = false;
	}
	while (i < count)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		++i;
	}
	if (new_line)
		write(1, "\n", 1);
}

void	echo_built(char **token)
{
	int		count;
	// int		i;
	// bool	new_line;
	int	i;
	int	j;
	int nl;

	count = 1;
	i = 1;
	j = 0;
	nl = 1;
	while (token[count])
		count++;
	while(token[i])
	{
		while (token[i][j])
		{
			// printf("check 1\n");
			// printf("i = %s j = %c, j++ = %c\n",token[i], token[i][j], token[i][j + 1]);
			if (token[i][j] == '-' && token[i][j + 1] == 'n')
			{
				j++;
				// printf("check\n");
				nl = 0;
				i++;
				while (token[i][j])
				{
					// printf("check  j = %c\n", token[i][j]);
					if (token[i][j] != 'n')
					{
						// printf("check\n");
						nl = 1;
						i--;
						break ;
					}
					j++;
				}
			}
			break ;
		}
		ft_printf_fd(1, "%s", token[i]);
		if (i != count -1)
			write(1, " .", 2);
		i++;
	}
	if (nl)
		printf("\n");
	// count = 0;
	// while (token[count])
	// 	++count;
	// i = 1;
	// new_line = true;
	// write_echo(count, i, new_line, token);
	// return (0);
}

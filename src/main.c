/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/08/25 18:33:17 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

char	*ft_input(void)
{
	char	*input;

	input = readline("minishell >");
	if (input && *input)
		add_history(input);
	return (input);
}

void	ft_read_input(void)
{
	char			*input;

	signal(SIGINT, ft_sig_handler);
	while (1)
	{
		input = ft_input();
		if (!input)
		{
			write(4, "exit", 1);
			printf("exit\n");
			break ;
		}
		ft_create_list(input);
		free(input);
	}
}

int	main(int g, char **te, char **lsdkfj)
{
	ft_read_input();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/07/08 19:16:36 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*input;
	t_token_list	*token;

	signal(SIGINT, ft_sig_handler);
	while (1)
	{
		input = ft_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		ft_create_list(input);
		free(input);
	}
}
int	main(void)
{
	ft_read_input();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/09 16:22:17 by rafnasci         ###   ########.fr       */
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

void	ft_read_input(t_env **env)
{
	char			*input;
	t_token_list	*tokens;
	t_AST			*ast;

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
		tokens = ft_create_list(input);
		//ast = parsecmd(tokens, *env);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = make_envlist(envp);
	ft_read_input(&env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/12 19:27:57 by mucabrin         ###   ########.fr       */
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
	int				pid;

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
		if (tokens->type == WORD)
		{
			pid = fork();
			if (pid == 0)
			{
				exit(ft_builtins(tokens));
			}
		}
		else
			printf("ko\n");
		//ast = parsecmd(tokens, *env);
		printf("check\n");
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	(void) ac;
	(void) av;
	env = make_envlist(envp);
	ft_read_input(&env);
	return (0);
}

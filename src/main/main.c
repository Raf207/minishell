/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/28 07:41:45 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		g_exitcode;

int	ft_lastchar(char *str)
{
	char	c;
	int		i;

	if (!str)
		return (-1);
	i = -1;
	c = str[0];
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			c = str[i];
	}
	return (c);
}

char	*ft_input(void)
{
	char	*input;
	char	*tmp;

	while (1)
	{
		input = readline("minishell$ ");
		while (ft_lastchar(input) == '|')
		{
			tmp = readline("> ");
			input = ft_strjoin(input, tmp);
			free(tmp);
		}
		if (!input || input[0])
			break ;
		free(input);
	}
	if (input && *input)
		add_history(input);
	if (!input)
		printf("exit\n");
	return (input);
}

void	ft_read_input(t_env **env)
{
	t_main	main;
	int		stock;

	main.copy_in = dup(0);
	main.copy_out = dup(1);
	while (1)
	{
		stock = ft_init(env, &main);
		if (stock == 0)
			break ;
		if (stock == 0)
			continue ;
		signal(SIGINT, ft_exec_sig_handler);
		signal(SIGQUIT, ft_exec_sig_handler);
		dup2(main.copy_in, STDIN_FILENO);
		dup2(main.copy_out, STDOUT_FILENO);
		ft_execpart(env, &main);
		ft_free(main.envp);
		ft_free_ast(main.ast);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	(void)ac;
	env = make_envlist(envp);
	if (!env)
	{
		ft_putendl_fd("malloc error", 2);
		return (1);
	}
	ft_read_input(&env);
	ft_free_env(&env);
	return (0);
}

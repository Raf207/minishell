/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:02:10 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/28 07:54:51 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_init(t_env **env, t_main *main)
{
	t_token_list	*tokens;
	char			*input;

	tokens = NULL;
	signal(SIGINT, ft_main_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	input = ft_input();
	input = ft_expansion(input, env);
	if (!input)
		return (0);
	main->envp = build_env(env);
	if (!main->envp)
		return (free(input), 1);
	if (ft_create_list(input, env, &tokens))
	{
		ft_free(main->envp);
		free(input);
		return (1);
	}
	g_exitcode = 0;
	main->ast = ft_parsing(&tokens);
	ft_cleantoken(&tokens);
	return (free(input), 2);
}

void	ft_execpart(t_env **env, t_main *main)
{
	if (main->ast && (main->ast)->type != N_PIPE
		&& ft_isbuiltin(ft_findexec(main->ast)))
	{
		ft_runcmd(main->ast, main->envp, env);
		close(1);
		dup2(main->copy_out, STDOUT_FILENO);
	}
	else if (main->ast)
	{
		main->pid = ft_fork1();
		if (!main->pid)
		{
			ft_runcmd(main->ast, main->envp, env);
			ft_free_ast(main->ast);
			exit(0);
		}
		waitpid(main->pid, &(main->status), 0);
		if (g_exitcode != 131)
			g_exitcode = main->status / 256;
	}
}

int	ft_len_list(t_env **list)
{
	int		len;
	t_env	*node;

	len = 0;
	node = *list;
	while (node && ++len)
		node = node->next;
	return (len);
}

char	**build_env(t_env **env)
{
	t_env	*node;
	int		len;
	char	**envp;
	char	*tmp;

	len = ft_len_list(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	node = *env;
	len = 0;
	while (node)
	{
		if (node->value != NULL)
		{
			tmp = ft_strjoin(ft_strdup(node->name), "=");
			envp[len] = ft_strjoin(tmp, node->value);
			if (!envp[len++])
				return (NULL);
		}
		node = node->next;
	}
	envp[len] = 0;
	return (envp);
}

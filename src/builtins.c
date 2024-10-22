/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:05:22 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/22 17:19:13 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_builtins(t_token_list *token, t_env **env)
{
	t_env	*node;

	node = *env;
	if (ft_strncmp(token->value, "cd", INT_MAX) == 0)
	{
		cd(token, env);
		return (0);
	}
	else if (ft_strncmp(token->value, "pwd", INT_MAX) == 0)
	{
		pwd(env);
		return (0);
	}
	else if (ft_strncmp(token->value, "export", INT_MAX) == 0)
	{
		export(token, env);
		return (0);
	}
	else if (ft_strncmp(token->value, "env", INT_MAX) == 0)
	{
		while (node)
		{
			if (node->value)
				printf("%s=%s\n", node->name, node->value);
			node = node->next;
		}
	}
	else if (ft_strncmp(token->value, "exit", INT_MAX) == 0)
	{
		exit_built(token);
		return (0);
	}
	else if (ft_strncmp(token->value, "echo", INT_MAX) == 0
		&& ft_strncmp(token->next->value, "$?", INT_MAX) == 0)
	{
		echo_built();
		return (0);
	}
	else
		printf("NOT YET\n");
	return (1);
}

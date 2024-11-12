/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:05:22 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/12 18:23:23 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isbuiltin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	else
		return (0);
}

int	ft_builtins(char **token, t_env **env) 
{
	t_env	*node;

	if (!token)
		return (1);
	g_exitcode = 0;
	node = *env;
	if (ft_strncmp(token[0], "cd", INT_MAX) == 0)
	{
		cd(token, env);
		return (0);
	}
	else if (ft_strncmp(token[0], "pwd", INT_MAX) == 0)
	{
		pwd(env);
		return (0);
	}
	else if (ft_strncmp(token[0], "export", INT_MAX) == 0)
	{
		export(token, env);
		return (0);
	}
	else if (ft_strncmp(token[0], "unset", INT_MAX) == 0)
	{
		unset(token, env);
		return (0);
	}
	else if (ft_strncmp(token[0], "env", INT_MAX) == 0)
	{
		while (node)
		{
			if (node->value)
				ft_printf_fd(1, "%s=%s\n", node->name, node->value);
			else if (!node->value && node->equal)
				ft_printf_fd(1, "%s=\n", node->name);
			node = node->next;
		}
		ft_printf_fd(1, "_=/usr/bin/env\n");
		return (0);
	}
	else if (ft_strncmp(token[0], "exit", INT_MAX) == 0)
	{
		exit_built(token);
		return (0);
	}
	else if (ft_strncmp(token[0], "echo", INT_MAX) == 0)
	{
		echo_built(token);
		return (0);
	}
	return (1);
}
// check "command" '(' g_exitcode = 258
// and all error in the exec ¿g_exitcode = 1?
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:05:22 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/24 17:53:08 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isbuiltin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	else
		return (0);
}

static int	ft_env(t_env *node)
{
	if (!node)
		return (1);
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

int	ft_builtins(char **token, t_env **env)
{
	t_env	*node;

	if (!token[0])
		return (1);
	g_exitcode = 0;
	node = *env;
	if (ft_strncmp(token[0], "cd", INT_MAX) == 0)
		return (cd(token, env), 0);
	else if (ft_strncmp(token[0], "pwd", INT_MAX) == 0)
		return (pwd(env), 0);
	else if (ft_strncmp(token[0], "export", INT_MAX) == 0)
		return (export(token, env), 0);
	else if (ft_strncmp(token[0], "unset", INT_MAX) == 0)
		return (unset(token, env), 0);
	else if (ft_strncmp(token[0], "env", INT_MAX) == 0)
	{
		if (!ft_env(node))
			return (0);
	}
	else if (ft_strncmp(token[0], "exit", INT_MAX) == 0)
		return (exit_built(token), 0);
	else if (ft_strncmp(token[0], "echo", INT_MAX) == 0)
		return (echo_built(token), 0);
	return (1);
}
// check "command" '(' || '<' g_exitcode = 258
// and all error in the exec ¿g_exitcode = 1?
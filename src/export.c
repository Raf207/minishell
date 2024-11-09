/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:12:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/08 21:11:09 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_char(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}

static int	envchr(char *name, t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, INT_MAX))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	set_value(char *name, char *value, t_env **env, int p)
{
	t_env	*top;

	top = *env;
	while ((*env) && p)
	{
		if (!ft_strncmp((*env)->name, name, INT_MAX))
		{
			free((*env)->value);
			(*env)->value = value;
			(*env)->equal = p;
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = top;
}

static void	set_var(char *str, t_env **env)
{
	t_env	*top;
	int		len;
	char	*name;
	char	*value;
	int		p;

	len = find_char(str, '=');
	name = ft_substr(str, 0, len);
	value = ft_substr(str, len + 1, INT_MAX);
	if (ft_strchr(str, '='))
		p = 1;
	else
		p = 0;
	if (envchr(name, *env))
		set_value(name, value, env, p);
	else
		append_list(env, str);
}

void	export(t_token_list *token, t_env **env)
{
	t_env	*export;
	t_env	*top;

	if (!token->next->value)
	{
		sort_env(*env);
		return ;
	}
	token = token->next;
	while (token->next)
	{
		if (!check_identifier(token->value))
		{
			ft_printf_fd(2, "bash: export: %s: not a valid identifier\n",
				token->value);
			g_exitcode = 1;
		}
		else
			set_var(token->value, env);
		token = token->next;
		// else if (!export(!token->value, env))
		// 	return (print_error);
	}
}

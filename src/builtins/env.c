/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:04:10 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/30 17:39:03 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*ft_last_node(t_env *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

static int	find_char(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}

void	append_list(t_env **env_list, char *str)
{
	t_env	*node;
	t_env	*last_node;
	int		len;

	if (!env_list)
		return ;
	node = calloc(1, sizeof(t_env));
	if (!node)
		return ;
	node->next = NULL;
	len = find_char(str, '=');
	if (ft_strchr(str, '='))
		node->equal = true;
	else
		node->equal = false;
	node->name = ft_substr(str, 0, len);
	if (node->equal)
		node->value = ft_substr(str, len + 1, INT_MAX);
	if (!(*env_list))
		*env_list = node;
	else
	{
		last_node = ft_last_node(*env_list);
		last_node->next = node;
	}
}

void	ft_shlvl(t_env **env)
{
	t_env	*last;
	int		lvl;

	last = ft_last_node(*env);
	lvl = ft_atoi(last->value);
	lvl++;
	free(last->value);
	last->value = ft_itoa(lvl);
}

t_env	*make_envlist(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "./minishell", 100000000))
			;
		else if (ft_strncmp(env[i], "OLDPWD", 5))
			append_list(&env_list, env[i]);
		if (ft_strncmp(env[i], "SHLVL", 5) == 0)
			ft_shlvl(&env_list);
	}
	append_list(&env_list, "OLDPWD");
	return (env_list);
}

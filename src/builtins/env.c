/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:04:10 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/25 16:00:49 by rafnasci         ###   ########.fr       */
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

static int	append_list(t_env **env_list, char *str)
{
	t_env	*node;
	t_env	*last_node;
	int		len;

	if (!env_list)
		return (0);
	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->next = NULL;
	len = find_char(str, '=');
	node->name = ft_substr(str, 0, len);
	node->value = ft_substr(str, len + 1, INT_MAX);
	if (!node->name || !node->value)
		return (0);
	if (!(*env_list))
		*env_list = node;
	else
	{
		last_node = ft_last_node(*env_list);
		last_node->next = node;
	}
	return (1);
}

char	**build_env(t_env	**env)
{
	t_env	*node;
	int		len;
	char	**envp;
	char	*tmp;

	len = 0;
	node = *env;
	while (node && ++len)
		node = node->next;
	envp = calloc(sizeof(char *), (len + 1));
	if (!envp)
		return (NULL);
	envp[len] = 0;
	node = *env;
	len = 0;
	while (node)
	{
		tmp = ft_strjoin(node->name, "=");
		envp[len] = ft_strjoin(tmp, node->value);
		if (!envp[len++])
			return (ft_free(envp), NULL);
		free(tmp);
		node = node->next;
	}
	return (envp);
}

t_env	*make_envlist(char	**env)
{
	t_env	*env_list;
	int		i;

	i = -1;
	env_list = NULL;
	while (env[++i])
	{
		if (!append_list(&env_list, env[i]))
			return (ft_free_env(&env_list), NULL);
	}
	return (env_list);
}

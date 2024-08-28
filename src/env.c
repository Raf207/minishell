/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:04:10 by rafnasci          #+#    #+#             */
/*   Updated: 2024/08/28 04:18:08 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*ft_last_node(t_env *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

static int	find_char(const char	*str, int c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}

static void	append_list(t_env **env_list, char *str)
{
	t_env	*node;
	t_env	*last_node;
	int		len;

	if (!env_list)
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->next = NULL;
	len = find_char(str, '=');
	node->name = ft_substr(str, 0, len);
	node->value = ft_substr(str, len + 1, INT_MAX);
	printf("%s=%s\n", node->name, node->value);
	if (!(*env_list))
		*env_list = node;
	else
	{
		last_node = ft_last_node(*env_list);
		last_node->next = node;
	}
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
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	envp[len] = 0;
	node = *env;
	len = 0;
	while (node)
	{
		tmp = ft_strjoin(node->name, "=");
		envp[len] = ft_strjoin(tmp, node->value);
		if (!tmp || !envp[len++])
			return (NULL);
		free(tmp);
		node = node->next;
	}
	return (envp);
}

t_env	*make_envlist(char	**env)
{
	t_env	*env_list = NULL;
	int		i;

	i = -1;
	while (env[++i])
		append_list(&env_list, env[i]);
	return (env_list);
}

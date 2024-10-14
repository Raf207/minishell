/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:04:10 by rafnasci          #+#    #+#             */
/*   Updated: 2024/10/14 16:37:01 by mucabrin         ###   ########.fr       */
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
/*
	petite fonction pour chercher un carctere, principalement utilisee
	pour trouver le = dans l'environnement
	pour pouvoir separer ce qu'il y a avant et apres
*/

static int	find_char(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}
/*
	ajoute une ligne de l'environnement en tant que node dans la liste
*/
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
	if (ft_strncmp(node->name, "OLDPWD", INT_MAX) != 0)
		node->value = ft_substr(str, len + 1, INT_MAX);
	else 
		node->value = NULL;
	if (!(*env_list))
		*env_list = node;
	else
	{
		last_node = ft_last_node(*env_list);
		last_node->next = node;
	}
}
/*
	cree un tableau de la liste de l'environnement donne
*/
char	**build_env(t_env **env)
{
	t_env	*node;
	int		len;
	char	**envp;
	char	*tmp;

	len = 0;
	node = *env;
	while (node && ++len)
	{
		//printf("env->name : %s\n env->value : %s\n", node->name,
		//	node->value);
		node = node->next;
	}
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	node = *env;
	len = 0;
	while (node)
	{
		if(node->value != NULL)
		{
			tmp = ft_strjoin(node->name, "=");
			envp[len] = ft_strjoin(tmp, node->value);
			if (!tmp || !envp[len++])
				// ici il faut free tmp seulement si envp[len] retourne NULL mais j'ai pas les lignes faudra voir comment faire;
				return (NULL);
			free(tmp);
		}
		node = node->next;
	}
	envp[len] = 0;
	return (envp);
}

/*
	cree une liste chainee de l'environnement comme on l'avait dit
*/
t_env	*make_envlist(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = -1;
	while (env[++i])
		append_list(&env_list, env[i]);
	return (env_list);
}

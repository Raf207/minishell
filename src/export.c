/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:12:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/22 17:25:47 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void	swap_list(t_env **list)
{
	t_env	*tmp;

	tmp = *list;
	*list = (*list)->next;
	tmp->next = (*list)->next;
	(*list)->next = tmp;
}

static int	listlen(t_env *list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_env	*ft_sortlist(t_env **env)
{
	t_env	*list;
	int		i;
	int		j;
	int		len;
	t_env	*tmp;
	int	t = 0;

	list = *env;
	i = 1;
	len = listlen(list);
	tmp = list;
	while (i < len)
	{
		list = tmp;
		while (list)
		{
			printf("name %s next %s\n", list->name, list->next->name);
			if (ft_strcmp(list->name, list->next->name) > 0)
				swap_list(&list);
			list = list->next;
		}
		i++;
	}
	list = tmp;
	while (list)
	{
		printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (list);
}

void	export(t_token_list *token, t_env **env)
{
	t_env	*export;

	export = ft_sortlist(env);
	//if (!token->next->value)
	//{
	//	while (export)
	//	{
	//		printf("declare -x %s", export->name);
	//		if (!export->value)
	//			printf("\n");
	//		if (export->value)
	//			printf("=\"%s\"\n", export->value);
	//		export = export->next;
	//	}
	//}
}

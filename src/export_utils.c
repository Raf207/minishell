/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:05:23 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/02 17:51:05 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	listlen(t_env *list)
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

void	free_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_node(tmp);
		tmp = NULL;
	}
}

//int	check_identifier(char *str)
//{
//	int	i;

//	i = 0;
//	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
//		return (0);
//	while (str[i] && str[i] != '=')
//	{
//		if (!ft_isalnum(str[i]) && str[i] != '_')
//			return (0);
//		i++;
//	}
//	return (1);
//}

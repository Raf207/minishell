/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:49:38 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/18 15:17:30 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\r' || c == '\n'
		|| c == '\f' || c == '\v' || c == '\t');
}

t_token_list	*ft_last_token(t_token_list *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_append_list(t_token_list **list, t_token_typ	type, char *value)
{
	t_token_list	*node;
	t_token_list	*last_node;

	if (!list)
		return ;
	node = malloc(sizeof(t_token_list));
	if (!node)
		return ;
	node->next = NULL;
	node->type = type;
	node->value = ft_strdup(value);
	if (!(*list))
	{
		*list = node;
		node->prev = NULL;
	}
	else
	{
		last_node = ft_last_token((*list));
		last_node->next = node;
		node->prev = last_node;
	}
}

void	ft_cleantoken(t_token_list **list)
{
	t_token_list	*temp;
	t_token_list	*current;

	if (!list)
		return ;
	current = *list;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
	*list = NULL;
}

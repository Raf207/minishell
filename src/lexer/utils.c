/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:49:38 by rafnasci          #+#    #+#             */
/*   Updated: 2024/10/19 20:21:12 by rafnasci         ###   ########.fr       */
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

int	ft_append_list(t_token_list **list, t_token_typ	type, char *value)
{
	t_token_list	*node;
	t_token_list	*last_node;

	if (!list || (!value && type != END))
		return (0);
	node = malloc(sizeof(t_token_list));
	if (!node)
		return (0);
	node->next = NULL;
	node->type = type;
	node->value = ft_strdup(value);
	if (!node->value && type != END)
		return (0);
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
	return (1);
}

void	ft_cleantoken(t_token_list **list)
{
	t_token_list	*temp;
	t_token_list	*current;

	if (!list || !(*list))
		return ;
	current = *list;
	while (current)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	*list = NULL;
}

void	ft_update_tok(t_token_list **token)
{
	t_token_list	*temp;
	int				i;

	temp = *token;
	while (temp->next)
	{
		if (ft_strncmp("$?", temp->value, 2) == 0)
		{
			free(temp->next->value);
			temp->next->value = ft_strdup("numero de exit");
		}
		if (ft_strncmp("echo", temp->value, 5) == 0)
		{
			if (temp->next->value[0] == '-' && temp->next->value[1] == 'n')
			{
				i = 1;
				while (temp->next->value[++i])
					if (temp->next->value[i] != 'n')
						return ;
				free(temp->next->value);
				temp->next->value = ft_strdup("-n");
			}
		}
		temp = temp->next;
	}
}

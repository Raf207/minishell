/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:49:38 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/28 23:58:22 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	t_token_list	*tm;

	tm = *token;
	while (tm->value)
	{
		if (ft_strncmp("~", tm->value, 1) == 0)
		{
			free(tm->value);
			tm->value = ft_strjoin(ft_strdup(getenv("HOME")), &tm->value[1]);
		}
		tm = tm->next;
	}
}

int	ft_endtok(t_token_list **tokens, t_enfin *enfin)
{
	if (!ft_append_list(tokens, END, NULL))
		ft_exit_tokens(tokens, "minishell: malloc error");
	if (enfin->in_quote)
		return (ft_cleantoken(tokens), printf("minishell: syntax error\n"), 1);
	ft_update_tok(tokens);
	return (0);
}

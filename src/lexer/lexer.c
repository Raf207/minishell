/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:06:24 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/16 21:18:30 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\r' || c == '\n'
		|| c == '\f' || c == '\v' || c == '\t');
}

static t_token_list	*ft_last_token(t_token_list *list)
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

t_token_list	*ft_create_list(char *input)
{
	t_token_list	*tokens;
	int				i;
	char			*current;
	int				word_len;
	int				in_quote;
	char			quote;

	tokens = NULL;
	current = (char *) malloc (sizeof(char) * (ft_strlen(input) + 1));
	word_len = 0;
	i = -1;
	quote = '\0';
	in_quote = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (!in_quote)
			{
				in_quote++;
				quote = input[i];
			}
			else if (in_quote && input[i] == quote)
			{
				in_quote--;
				quote = '\0';
			}
			continue ;
		}
		if (in_quote)
		{
			current[word_len++] = input[i];
			continue ;
		}
		if (ft_isspace(input[i]))
		{
			if (word_len > 0)
			{
				current[word_len] = '\0';
				ft_append_list(&tokens, WORD, current);
				word_len = 0;
			}
			continue ;
		}

		if (input[i] == '>')
		{
			if (word_len > 0)
			{
				current[word_len] = '\0';
				ft_append_list(&tokens, WORD, current);
				word_len = 0;
			}
			if (input[i + 1] == '>')
			{
				ft_append_list(&tokens, RED_APPEND, ">>");
				i++;
			}
			else
				ft_append_list(&tokens, RED_OUT, ">");
			continue ;
		}

		if (input[i] == '<')
		{
			if (word_len > 0)
			{
				current[word_len] = '\0';
				ft_append_list(&tokens, WORD, current);
				word_len = 0;
			}
			if (input[i + 1] == '<')
			{
				ft_append_list(&tokens, HEREDOC, "<<");
				i++;
			}
			else
				ft_append_list(&tokens, RED_IN, "<");
			continue ;
		}

		if (input[i] == '|')
		{
			if (word_len > 0)
			{
				current[word_len] = '\0';
				ft_append_list(&tokens, ASSIGNEMENT, current);
				word_len = 0;
			}
			ft_append_list(&tokens, PIPE, "|");
			continue ;
		}

		if (input[i] == '=')
		{
			if (word_len > 0)
			{
				current[word_len] = '\0';
				ft_append_list(&tokens, ASSIGNEMENT, current);
				word_len = 0;
			}
			ft_append_list(&tokens, EQUALS, "=");
			continue ;
		}

		current[word_len++] = input[i];
	}
	if (word_len > 0)
	{
		current[word_len] = '\0';
		ft_append_list(&tokens, WORD, current);
		word_len = 0;
	}
	ft_append_list(&tokens, END, NULL);
	// t_token_list	*temp;
	// temp = tokens;
	// while (temp)
	// {
	// 	printf("%s\n", temp->value);
	// 	temp = temp->next;
	// }
	// ft_cleantoken(&tokens);
	return(tokens);
}

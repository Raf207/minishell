/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:06:24 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/17 21:46:12 by rafnasci         ###   ########.fr       */
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

char *ft_expansion(char *str, t_env **env)
{
	int		i;
	int		j;
	t_env	*start;
	int		tot;
	int		len;
	char	*rep;

	i = -1;
	tot = 0;
	len = ft_strlen(str);
	while (str[++i])
	{
		j = 0;
		start = *env;
		if (str[i] == '$')
		{
			while (str[i + j + 1] && !ft_isspace(str[i + j + 1]))
				j++;
			len -= j + 1;
			while (start)
			{
				if (ft_strncmp(start->name, &str[i + 1], j) == 0
					&& start->name[j] == 0)
				{
					len += ft_strlen(start->value);
					break ;
				}
				start = start->next;
			}
		}
	}
	tot = len;
	printf("tot : %d\n", len);
	rep = malloc(sizeof(char) * tot + 1);
	rep[tot] = 0;
	i = -1;
	tot = 0;
	while (str[++i])
	{
		j = 0;
		start = *env;
		if (str[i] == '$')
		{
			while (str[i + j + 1] && !ft_isspace(str[i + j + 1]))
				j++;
			len -= j + 1;
			while (start)
			{
				if (ft_strncmp(start->name, &str[i + 1], j) == 0
					&& start->name[j] == 0)
				{
					ft_strlcpy(&rep[tot], start->value, ft_strlen(start->value) + 1);
					tot += ft_strlen(start->value);
					break ;
				}
				start = start->next;
			}
			i += j;
		}
		else
			rep[tot++] = str[i];
	}
	return (rep);
}

t_token_list	*ft_create_list(char *input, t_env **env)
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
				continue ;
			}
			else if (in_quote && input[i] == quote)
			{
				in_quote--;
				current[word_len] = '\0';
				if (word_len > 0)
				{
					if (quote == '\'')
						ft_append_list(&tokens, WORD, current);
					else
						ft_append_list(&tokens, WORD, ft_expansion(current, env));
					word_len = 0;	
				}
				quote = '\0';
				continue ;
			}
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
	if (in_quote)
		printf("erreur syntax\n");
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

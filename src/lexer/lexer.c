/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:06:24 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/27 03:41:11 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_tok(t_token_list **tokens, char *value, t_enfin *enfin,
		t_token_typ type)
{
	char	*temp;

	if (!value)
	{
		if ((enfin->word_len > 0 || (enfin->i != 0 && enfin->input[enfin->i
					- 1] == '"' && enfin->word_len == 0) || (enfin->i != 0
					&& enfin->input[enfin->i - 1] == '\''
					&& enfin->word_len == 0)))
		{
			enfin->current[enfin->word_len] = '\0';
			temp = ft_strdup(enfin->current);
			if (!ft_append_list(tokens, type, temp))
			{
				free(temp);
				ft_exit_tokens(tokens, "minishell: malloc error");
			}
			free(temp);
			enfin->word_len = 0;
		}
	}
	else
	{
		if (!ft_append_list(tokens, type, value))
			ft_exit_tokens(tokens, "minishell: malloc error");
	}
}

int	new_redir(t_token_list **tokens, char *input, t_enfin *enfin)
{
	if (input[enfin->i] == '>')
	{
		new_tok(tokens, NULL, enfin, WORD);
		if (input[enfin->i + 1] == '>')
		{
			new_tok(tokens, ">>", enfin, RED_APPEND);
			enfin->i++;
		}
		else
			new_tok(tokens, ">", enfin, RED_OUT);
		return (1);
	}
	if (input[enfin->i] == '<')
	{
		new_tok(tokens, NULL, enfin, WORD);
		if (input[enfin->i + 1] == '<')
		{
			new_tok(tokens, "<<", enfin, HEREDOC);
			enfin->i++;
		}
		else
			new_tok(tokens, "<", enfin, RED_IN);
		return (1);
	}
	return (0);
}

int	new_pass(t_token_list **tokens, char *input, t_enfin *enfin)
{
	if (enfin->in_quote)
	{
		enfin->current[enfin->word_len++] = input[enfin->i];
		return (1);
	}
	if (input[enfin->i] == '|')
	{
		new_tok(tokens, NULL, enfin, WORD);
		if (!ft_append_list(tokens, PIPE, "|"))
			ft_exit_tokens(tokens, "minishell: malloc error");
		return (1);
	}
	if (ft_isspace(input[enfin->i]))
	{
		if (enfin->i == 0)
			enfin->word_len = 0;
		else
			new_tok(tokens, NULL, enfin, WORD);
		return (1);
	}
	return (0);
}

int	quotes_tok(t_token_list **tokens, char *input, t_enfin *enfin)
{
	(void)tokens;
	if ((input[enfin->i] == '\'' || input[enfin->i] == '"') && (enfin->i == 0
			|| (enfin->i != 0 && input[enfin->i - 1] != '\\')))
	{
		if (!enfin->in_quote)
		{
			enfin->in_quote++;
			enfin->quote = input[enfin->i];
			return (1);
		}
		else if (enfin->in_quote && input[enfin->i] == enfin->quote)
		{
			enfin->in_quote--;
			return (1);
		}
	}
	return (0);
}

int	ft_create_list(char *input, t_env **env, t_token_list **tokens)
{
	t_enfin	enfin;

	enfin.current = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	enfin.word_len = 0;
	enfin.i = -1;
	enfin.quote = '\0';
	enfin.in_quote = 0;
	enfin.env = env;
	enfin.input = input;
	while (input[++enfin.i])
	{
		if (input[enfin.i] == '\\' && input[enfin.i + 1])
			enfin.i++;
		if (quotes_tok(tokens, input, &enfin))
			continue ;
		if (new_pass(tokens, input, &enfin))
			continue ;
		if (new_redir(tokens, input, &enfin))
			continue ;
		enfin.current[enfin.word_len++] = input[enfin.i];
	}
	new_tok(tokens, NULL, &enfin, WORD);
	free(enfin.current);
	if (!ft_append_list(tokens, END, NULL))
		ft_exit_tokens(tokens, "minishell: malloc error");
	if (enfin.in_quote)
		return (ft_cleantoken(tokens), printf("minishell: syntax error\n"), 1);
	ft_update_tok(tokens);
	return (0);
}

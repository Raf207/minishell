/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:06:24 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/23 16:29:50 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_tok(t_token_list **tokens, t_env **env, t_enfin *enfin,
			t_token_typ type)
{
	if (enfin->word_len > 0)
	{
		enfin->current[enfin->word_len] = '\0';
		if (!ft_append_list(tokens, type, ft_expansion(enfin->current, env)))
			ft_exit_tokens(tokens);
		enfin->word_len = 0;
	}
}

int	new_redir(t_token_list **tokens, t_env **env, char *input, t_enfin *enfin)
{
	if (input[enfin->i] == '>')
	{
		new_tok(tokens, env, enfin, WORD);
		if (input[enfin->i + 1] == '>')
		{
			ft_append_list(tokens, RED_APPEND, ">>");
			enfin->i++;
		}
		else
			ft_append_list(tokens, RED_OUT, ">");
		return (1);
	}
	if (input[enfin->i] == '<')
	{
		new_tok(tokens, env, enfin, WORD);
		if (input[enfin->i + 1] == '<')
		{
			ft_append_list(tokens, HEREDOC, "<<");
			enfin->i++;
		}
		else
			ft_append_list(tokens, RED_IN, "<");
		return (1);
	}
	return (0);
}

int	new_pass(t_token_list **tokens, t_env **env, char *input, t_enfin *enfin)
{
	if (enfin->in_quote)
	{
		enfin->current[enfin->word_len++] = input[enfin->i];
		return (1);
	}
	if (input[enfin->i] == '|')
	{
		new_tok(tokens, env, enfin, WORD);
		ft_append_list(tokens, PIPE, "|");
		return (1);
	}
	if (input[enfin->i] == '=')
	{
		new_tok(tokens, env, enfin, ASSIGNEMENT);
		ft_append_list(tokens, EQUALS, "=");
		return (1);
	}
	if (ft_isspace(input[enfin->i]))
	{
		new_tok(tokens, env, enfin, WORD);
		return (1);
	}
	return (0);
}

int	quotes_tok(t_token_list **tokens, t_env **env, char *input, t_enfin *enfin)
{
	if (input[enfin->i] == '\'' || input[enfin->i] == '"')
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
			enfin->current[enfin->word_len] = '\0';
			if (enfin->word_len > 0 && enfin->quote == '\'')
				ft_append_list(tokens, WORD, enfin->current);
			else if (enfin->quote == '"')
				new_tok(tokens, env, enfin, WORD);
			enfin->word_len = 0;
			enfin->quote = '\0';
			return (1);
		}
	}
	return (0);
}

void	ft_create_list(char *input, t_env **env, t_token_list **tokens)
{
	t_enfin	enfin;

	enfin.current = (char *) malloc (sizeof(char) * (ft_strlen(input) + 1));
	enfin.word_len = 0;
	enfin.i = -1;
	enfin.quote = '\0';
	enfin.in_quote = 0;
	while (input[++enfin.i])
	{
		if (quotes_tok(tokens, env, input, &enfin))
			continue ;
		if (new_pass(tokens, env, input, &enfin))
			continue ;
		if (new_redir(tokens, env, input, &enfin))
			continue ;
		enfin.current[enfin.word_len++] = input[enfin.i];
	}
	new_tok(tokens, env, &enfin, WORD);
	if (!ft_append_list(tokens, END, NULL))
		ft_exit_tokens(tokens);
	if (enfin.in_quote)
	{
		ft_cleantoken(tokens);
		ft_panic("syntax");
	}
}

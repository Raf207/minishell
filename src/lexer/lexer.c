/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:06:24 by rafnasci          #+#    #+#             */
/*   Updated: 2024/10/19 20:06:01 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_tok(t_token_list **tokens, char *value, t_enfin *enfin,
			t_token_typ type)
{
	if (!value)
	{
		if (enfin->word_len > 0)
		{
			enfin->current[enfin->word_len] = '\0';
			if (!ft_append_list(tokens, type,
					ft_expansion(enfin->current, enfin->env)))
				ft_exit_tokens(tokens, "malloc");
			enfin->word_len = 0;
		}
	}
	else
	{
		if (!ft_append_list(tokens, type, value))
			ft_exit_tokens(tokens, "malloc");
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
			ft_exit_tokens(tokens, "malloc");
		return (1);
	}
	if (input[enfin->i] == '=')
	{
		new_tok(tokens, NULL, enfin, ASSIGNEMENT);
		if (!ft_append_list(tokens, EQUALS, "="))
			ft_exit_tokens(tokens, "malloc");
		return (1);
	}
	if (ft_isspace(input[enfin->i]))
	{
		new_tok(tokens, NULL, enfin, WORD);
		return (1);
	}
	return (0);
}

int	quotes_tok(t_token_list **tokens, char *input, t_enfin *enfin)
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
			{
				if (!ft_append_list(tokens, WORD, enfin->current))
					ft_exit_tokens(tokens, "malloc");
			}
			else if (enfin->quote == '"')
				new_tok(tokens, NULL, enfin, WORD);
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
	enfin.env = env;
	while (input[++enfin.i])
	{
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
		ft_exit_tokens(tokens, "malloc");
	if (enfin.in_quote)
		ft_exit_tokens(tokens, "syntax");
	ft_update_tok(tokens);
}

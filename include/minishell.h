/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:53 by rafnasci          #+#    #+#             */
/*   Updated: 2024/07/12 01:06:10 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "../libft/include/libft.h"

typedef enum e_toke
{
	END,
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	OR,
	AND,
	L_BRACKET,
	R_BRACKET,
	ASSIGNEMENT,
	EQUALS,
	PRE_WILDCARD,
	AFTER_WILDCARD,
	WILDCARD
}	t_token_typ;

typedef struct s_token_list
{
	struct s_token_list	*prev;
	struct s_token_list	*next;
	t_token_typ			type;
	char				*value;
}	t_token_list;

t_token_list	*ft_create_list(char *input);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:53 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/12 20:26:24 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <curses.h>
# include <errno.h> // mucabrin
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include <unistd.h>
# include <fcntl.h>
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
	ASSIGNEMENT,
	EQUALS,
}						t_token_typ;

typedef enum e_node
{
	EXEC,
	REDIR,
	N_PIPE,
	N_HEREDOC,
}	t_node_type;

typedef struct s_token_list
{
	struct s_token_list	*prev;
	struct s_token_list	*next;
	t_token_typ			type;
	char				*value;
}						t_token_list;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*subcmd;
	char				*file;
	int					mode;
	int					fd;
	char				**argv;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_AST;

typedef struct s_env
{
	struct s_env		*next;
	char				*name;
	char				*value;
}						t_env;

t_token_list			*ft_create_list(char *input);
t_AST					*parsecmd(t_token_list *tokens, t_env *env);
t_env					*make_envlist(char **env);
char					**build_env(t_env **env);

// mucabrin


int						ft_builtins(t_token_list *token);
void					pwd(void);
int						cd(t_token_list *token);
t_token_list	*ft_create_list(char *input);
t_AST			*parsecmd(t_token_list *tokens, t_env *env);
t_env			*make_envlist(char	**env);
char			**build_env(t_env	**env);
t_AST			*ft_parsing(t_token_list *list);

void 			ft_runcmd(t_AST *ast, char **envp);
int				ft_fork1(void);


#endif
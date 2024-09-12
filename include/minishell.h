/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:53 by rafnasci          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/10 19:45:56 by mucabrin         ###   ########.fr       */
=======
/*   Updated: 2024/09/11 18:18:22 by rafnasci         ###   ########.fr       */
>>>>>>> 3bf171290910576f335507c5f2012a337c6f89bd
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
# include <limits.h>
# include <signal.h>
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
}	t_token_typ;

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
}	t_token_list;

typedef struct s_ast_node
{
	t_node_type			type;				;
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
	struct s_env	*next;
	char			*name;
	char			*value;
}	t_env;

t_token_list	*ft_create_list(char *input);
t_AST			*parsecmd(t_token_list *tokens, t_env *env);
t_env			*make_envlist(char	**env);
char			**build_env(t_env	**env);
t_AST			*ft_parsing(t_token_list *list);
<<<<<<< HEAD
void			 ft_runcmd(t_AST *ast, char **envp);
=======
void 			ft_runcmd(t_AST *ast, char **envp);
>>>>>>> 3bf171290910576f335507c5f2012a337c6f89bd
int				ft_fork1(void);

#endif
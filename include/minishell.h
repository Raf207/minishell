/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:53 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/17 19:15:29 by rafnasci         ###   ########.fr       */
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

t_token_list	*ft_create_list(char *input, t_env **env);
t_AST			*parsecmd(t_token_list *tokens, t_env *env);
t_env			*make_envlist(char	**env);
char			**build_env(t_env	**env);

int				ft_fork1(void);

//execution
void			ft_runcmd(t_AST *ast, char **envp, int copy_in, int copy_out);
void			ft_execution(char **cmd, char **envp);
int				ft_findenv(char **envp, char *name);
void			ft_heredoc_input(int pipe[2], char *limiter);

//parsing
t_AST			*ft_parsing(t_token_list *list);
t_AST			*ft_pipenode(t_AST *right, t_AST *left);
t_AST			*ft_redirnode(t_AST *subcmd, char *file, int mode, int fd);
t_AST			*ft_heredocnode(t_AST *subcmd, char *limiter);
t_AST			*ft_execnode(void);
t_AST			*ft_addredir(t_AST *cmd, t_token_list **list);
char			**ft_addargv(char **argv, char *arg);

//tools
void			ft_panic(char *s);
void			ft_free(char **s);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:53 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/30 16:17:39 by rafnasci         ###   ########.fr       */
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
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include "../libft/include/libft.h"
# include <dirent.h>
# include <errno.h>

extern int	g_exitcode;

typedef enum e_token
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
	t_node_type			type;
	struct s_ast_node	*subcmd;
	char				*file;
	int					mode;
	int					fd;
	int					pipe[2];
	char				**argv;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_AST;

typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
	bool			equal;
}	t_env;

typedef struct s_enfin
{
	int				i;
	char			*current;
	char			*input;
	int				word_len;
	int				in_quote;
	char			quote;
	t_env			**env;
}	t_enfin;

typedef struct s_built
{
	t_env				*env_oldpwd;
	t_env				*env_pwd;
	t_env				*env_home;
	const char			*path;
	char				*tmp;
	DIR					*dir;
}	t_built;

typedef struct s_parse
{
	t_AST	**top;
	t_AST	*temp;
	t_AST	*temp2;
}	t_parse;

typedef struct s_exp
{
	int		i;
	int		tot;
	t_env	*en;
	char	c;
}	t_exp;

typedef struct s_main
{
	t_AST			*ast;
	char			**envp;
	int				copy_in;
	int				copy_out;
	int				status;
	pid_t			pid;
}	t_main;

t_AST	*parsecmd(t_token_list *tokens, t_env *env);
t_env	*make_envlist(char	**env);
char	**build_env(t_env	**env);

int		ft_fork1(void);
int		ft_isspace(char c);
int		*ft_boolhere(int i);
int		ft_init(t_env **env, t_main *main);
char	*ft_input(void);
void	ft_execpart(t_env **env, t_main *main);
int		ft_lastchar(char *str);

//lexer
int		ft_create_list(char *input, t_env **env, t_token_list **tokens);
int		ft_append_list(t_token_list **list, t_token_typ	type, char *value);
char	*ft_expansion(char *str, t_env **env);
void	ft_cleantoken(t_token_list **list);
void	ft_update_tok(t_token_list **token);
int		ft_endtok(t_token_list **tokens, t_enfin *enfin);
void	ft_checkcoma(char *str, char *c, int i, int mode);
void	ft_findinenv(t_env *start, char *str, int *len, int i);
int		ft_len(char	*str, int i);
int		ft_addexitcode(char *rep, char *str, int i, t_exp *p);
int		ft_isincoma(char *str);
void	ft_exitcode(int *len);

//execution
void	ft_runcmd(t_AST *ast, char **envp, t_env **env);
void	ft_execution(char **cmd, char **envp);
int		ft_findenv(char **envp, char *name);
int		ft_heredoc_input(int fd, char *limiter);
void	ft_pipe1(int p[2], t_AST *ast, char **envp, t_env **env);
void	ft_pipe2(int p[2], t_AST *ast, char **envp, t_env **env);

//parsing
t_AST	*ft_parsing(t_token_list **mlist);
t_AST	*ft_pipenode(t_AST *right, t_AST *left);
t_AST	*ft_redirnode(t_AST *subcmd, char *file, int mode, int fd);
t_AST	*ft_heredocnode(t_AST *subcmd, char *limiter);
t_AST	*ft_execnode(void);
t_AST	*ft_addredir(t_AST *cmd, t_token_list **list);
char	**ft_addargv(char **argv, char *arg);
char	*ft_findexec(t_AST	*cmd);

//tools
void	ft_panic(char *s);
void	ft_free(char **s);
int		ft_find_here(t_AST *ast);
void	ft_exit_tokens(t_token_list **tokens, char *s);
void	ft_free_ast(t_AST *node);
void	ft_free_env(t_env **list);

//signals
void	ft_hered_sig_handler(int sig);
void	ft_main_sig_handler(int sig);
void	ft_exec_sig_handler(int sig);

//builtins
int		ft_builtins(char **token, t_env **env);
void	pwd(t_env **env);
void	cd(char **token, t_env **env);
t_env	*ft_findnode(t_env *env, char *name);
void	cd_home(t_built *var);
void	cd_oldpwd(t_built *var);
void	cd_dir(t_built *var);
void	exit_built(char **token);
void	echo_built(char **token);
void	export(char **token, t_env **env);
void	sort_env(t_env *top);
int		listlen(t_env *list);
void	free_list(t_env *list);
void	free_node(t_env *node);
int		check_identifier(char *str);
void	unset(char **token, t_env **env);
void	append_list(t_env **env_list, char *str);
int		ft_isbuiltin(char *str);

#endif
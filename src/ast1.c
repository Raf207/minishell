/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:57:28 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/11 18:16:40 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
void	ft_panic(char *s)
{
	ft_putendl_fd(s, 2);
	exit (1);
}

int	ft_fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_panic("fork error");
	return (pid);
}

int	ft_findpath(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (i);
	return (-1);
}

void	ft_execution(char **cmd, char **envp)
{
	char	*path_envp;
	char	**all_paths;
	int		i;
	char	*path;

	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	path_envp = ft_substr(envp[ft_findpath(envp)], 5, 4654654);
	all_paths = ft_split(path_envp, ":");
	i = -1;
	while (all_paths[++i])
	{
		path = ft_strjoin(ft_strjoin(all_paths[i], "/"), cmd[0]);
		if (access(path, X_OK) == 0)
			execve(path, cmd, envp);
		free(path);
	}
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	ft_free(cmd);
	ft_free(all_paths);
	free(path_envp);
	exit(EXIT_FAILURE);
}

t_AST	*ft_execnode(void)
{
	t_AST	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (cmd);
}

t_AST	*ft_heredocnode(t_AST *subcmd, char *limiter, int mode)
{
	t_AST	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = HEREDOC;
	cmd->subcmd = subcmd;
	cmd->file = limiter;
	cmd->mode = mode;
	return (cmd);
}

t_AST	*ft_redirnode(t_AST *subcmd, char *file, int mode, int fd)
{
	t_AST	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->subcmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_AST	*ft_pipenode(t_AST *right, t_AST *left)
{
	t_AST	*cmd;

	cmd = malloc (sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = NPIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}

t_AST	*ft_parseredir(t_AST *cmd, t_token_list **list)
{
	t_token_typ	tok;

	while ((*list)->type == RED_IN || (*list)->type == RED_APPEND
		|| (*list)->type == RED_OUT)
	{
		tok = (*list)->type;
		(*list) = (*list)->next;
		if ((*list)->type != WORD)
			ft_panic("missing file for redirection");
		if (tok == RED_IN)
			cmd = ft_redirnode(cmd, (*list)->value, O_RDONLY, 0);
		else if (tok == RED_OUT)
			cmd = ft_redirnode(cmd, (*list)->value,
					O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == RED_APPEND)
			cmd = ft_redirnode(cmd, (*list)->value,
					O_WRONLY | O_CREAT | O_APPEND, 1);
		(*list) = (*list)->next;
	}
	return (cmd);
}

char	**ft_addargv(char **argv, char *arg)
{
	int		nb_args;
	char	**rep;

	if (!argv)
	{
		argv = malloc (sizeof(char *) * 2);
		if (!argv)
			return (NULL);
		argv[0] = ft_strdup(arg);
		if (!argv[0])
			return (free(argv), NULL);
		argv[1] = 0;
		return (argv);
	}
	nb_args = -1;
	while (argv[++nb_args])
		;
	rep = malloc(sizeof(char *) * (nb_args + 2));
	if (!rep)
		return (ft_free(argv), NULL);
	rep[nb_args + 1] = 0;
	rep[nb_args] = ft_strdup(arg);
	if (!rep)
		return (ft_free(argv), free(rep),NULL);
	while (--nb_args >= 0)
		rep[nb_args] = argv[nb_args];
	free(argv);
	return (rep);
}

t_AST	*ft_parseexec(t_token_list **list)
{
	t_AST		*cmd;
	t_AST		*top;
	t_token_typ	tok;
	char		**argv;

	top = ft_execnode();
	cmd = top;
	top = ft_parseredir(top, list);
	while ((*list)->type != PIPE)
	{
		tok = (*list)->type;
		if (tok == END)
			break ;
		if (tok != WORD)
			ft_panic("syntax");
		cmd->argv = ft_addargv(cmd->argv, (*list)->value);
		(*list) = (*list)->next;
		top = ft_parseredir(top, list);
	}
	return (top);
}

t_AST	*ft_parsepipe(t_token_list **list)
{
	t_AST	*cmd;

	cmd = ft_parseexec(list);
	if ((*list)->type == PIPE)
	{
		(*list) = (*list)->next;
		cmd = ft_pipenode(cmd, ft_parsepipe(list));
	}
	return (cmd);
}

t_AST	*ft_parsing(t_token_list *list)
{
	t_AST	*cmd;

	cmd = ft_parsepipe(&list);
	return (cmd);
}

void ft_runcmd(t_AST *ast, char **envp)
{
	int	p[2];
	int fd;

	if (!ast)
		exit(1);
	if (ast->type == EXEC)
	{
		if (!ast->argv[0])
			exit(1);
		ft_execution(ast->argv, envp);
		ft_putendl_fd(ft_strjoin(ast->argv[0], " failed to exec"), 2);
	}
	else if (ast->type == REDIR)
	{
		close(ast->fd);
		fd = open(ast->file, ast->mode, 0777);
		if (fd < 0)
		{
			ft_putendl_fd(ft_strjoin(ast->file, " failed to open"), 2);
			exit(1);
		}
		ft_runcmd(ast->subcmd, envp);
	}
	else if (ast->type == NPIPE)
	{
		if (pipe(p) < 0)
			ft_panic("pipe");
		if (ft_fork1() == 0)
		{
			close(STDOUT_FILENO);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			ft_runcmd(ast->right, envp);
		}
		if (ft_fork1() == 0)
		{
			close(STDIN_FILENO);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			ft_runcmd(ast->left, envp);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else
		ft_panic("runccmd");
	exit(0);
}

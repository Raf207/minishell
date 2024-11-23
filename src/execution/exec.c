/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:02:30 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/23 21:43:59 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir(t_AST *ast, char **envp, t_env **env)
{
	int	fd;

	fd = open(ast->file, ast->mode, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			ast->file);
		exit(1);
	}
	if (dup2(fd, ast->fd) == -1)
	{
		close(fd);
		ft_panic("minishell: dup2 error");
	}
	close(fd);
	if (!ast->subcmd)
		ft_runcmd(ast->subcmd, envp, env);
	else
		exit(0);
}

void	ft_heredoc(t_AST *ast, char **envp, t_env **env)
{
	int	fd;

	fd = open(".heredoc", O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			ast->file);
		exit(1);
	}
	if (dup2(fd, ast->fd) == -1)
	{
		close(fd);
		ft_panic("minishell: dup2");
	}
	close(fd);
	if (!ast->subcmd)
		ft_runcmd(ast->subcmd, envp, env);
	else
		exit(0);
}

void	ft_pipe(t_AST *ast, char **envp, t_env **env)
{
	int		p[2];
	int		stat1;
	int		stat2;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(p) < 0)
		ft_panic("pipe");
	pid1 = ft_fork1();
	if (pid1 == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		ft_runcmd(ast->right, envp, env);
		ft_free_ast(ast);
		exit(127);
	}
	pid2 = ft_fork1();
	if (pid2 == 0)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		ft_runcmd(ast->left, envp, env);
		ft_free_ast(ast);
		exit(127);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid1, &stat1, 0);
	waitpid(pid2, &stat2, 0);
	ft_printf_fd(2, "sortieee : %d\n", stat2 / 256);
	exit(stat2 / 256);
}

void	ft_exec(t_AST *ast, char **envp, t_env **env)
{
	if (!ast->argv && !ast->argv[0])
		exit(1);
	if (ft_builtins(ast->argv, env) == 0)
		return ;
	else
		ft_execution(ast->argv, envp);
}

void	ft_runcmd(t_AST *ast, char **envp, t_env **env)
{
	if (!ast)
		exit(1);
	if (ast->type == EXEC)
		ft_exec(ast, envp, env);
	else if (ast->type == REDIR)
		ft_redir(ast, envp, env);
	else if (ast->type == N_HEREDOC)
		ft_heredoc(ast, envp, env);
	else if (ast->type == N_PIPE)
		ft_pipe(ast, envp, env);
	else
	{
		ft_panic("minishell: runcmd");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:02:30 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/10 19:55:31 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir(t_AST *ast, char **envp, t_env **env)
{
	int	fd;

	fd = open(ast->file, ast->mode, 0644);
	if (fd < 0)
	{
		ft_putendl_fd(ft_strjoin(ast->file, " failed to open"), 2);
		exit(1);
	}
	if (dup2(fd, ast->fd) == -1)
	{
		close(fd);
		ft_panic("dup2");
	}
	close(fd);
	ft_runcmd(ast->subcmd, envp, env);
}

void	ft_heredoc(t_AST *ast, char **envp, t_env **env)
{
	int	fd;

	fd = open(".heredoc", O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putendl_fd(ft_strjoin(ast->file, " failed to open"), 2);
		exit(1);
	}
	if (dup2(fd, ast->fd) == -1)
	{
		close(fd);
		ft_panic("dup2");
	}
	close(fd);
	ft_runcmd(ast->subcmd, envp, env);
}

void	ft_pipe(t_AST *ast, char **envp, t_env **env)
{
	int		p[2];

	if (pipe(p) < 0)
		ft_panic("pipe");
	if (ft_fork1() == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		ft_runcmd(ast->right, envp, env);
		ft_free_ast(ast);
		exit(0);
	}
	if (ft_fork1() == 0)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		ft_runcmd(ast->left, envp, env);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

void	ft_exec(t_AST *ast, char **envp, t_env **env)
{
	if (!ast->argv[0])
		exit(1);
	if (ft_builtins(ast->argv, env) == 0)
		return ;
	else
		ft_execution(ast->argv, envp);
	ft_putendl_fd(ft_strjoin(ast->argv[0], " failed to exec"), 2);
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
		ft_panic("runcmd");
}

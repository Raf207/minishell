/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:02:30 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/16 01:09:58 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir(t_AST *ast, char **envp, int copy_in)
{
	int	fd;

	fd = open(ast->file, ast->mode, 0644);
	if (fd < 0)
	{
		ft_putendl_fd(ft_strjoin(ast->file, " failed to open"), 2);
		exit(1);
	}
	if (dup2(fd, ast->fd) == -1)
		ft_panic("dup2");
	ft_runcmd(ast->subcmd, envp, copy_in);
}

void	ft_heredoc(t_AST *ast, char **envp, int copy_in)
{
	int	p_h[2];

	if (dup2(copy_in, STDIN_FILENO) == -1)
		ft_panic("dup2");
	close(copy_in);
	if (pipe(p_h) < 0)
		ft_panic("pipe");
	if (ft_fork1() == 0)
		ft_heredoc_input(p_h, ast->file);
	else
	{
		close(p_h[1]);
		dup2(p_h[0], STDIN_FILENO);
		close(p_h[0]);
		wait(NULL);
	}
	ft_runcmd(ast->subcmd, envp, copy_in);
}

void	ft_pipe(t_AST *ast, char **envp, int copy_in)
{
	int	p[2];

	if (pipe(p) < 0)
		ft_panic("pipe");
	if (ft_fork1() == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		ft_runcmd(ast->right, envp, copy_in);
	}
	if (ft_fork1() == 0)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		ft_runcmd(ast->left, envp, copy_in);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

void	ft_exec(t_AST *ast, char **envp)
{
	if (!ast->argv[0])
		exit(1);
	ft_execution(ast->argv, envp);
	ft_putendl_fd(ft_strjoin(ast->argv[0], " failed to exec"), 2);
}

void	ft_runcmd(t_AST *ast, char **envp, int copy_in)
{
	if (!ast)
		exit(1);
	if (ast->type == EXEC)
		ft_exec(ast, envp);
	else if (ast->type == REDIR)
		ft_redir(ast, envp, copy_in);
	else if (ast->type == N_HEREDOC)
		ft_heredoc(ast, envp, copy_in);
	else if (ast->type == N_PIPE)
		ft_pipe(ast, envp, copy_in);
	else
		ft_panic("runccmd");
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:55:27 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/15 19:56:51 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_AST	*ft_execnode(void)
{
	t_AST	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (cmd);
}

t_AST	*ft_heredocnode(t_AST *subcmd, char *limiter)
{
	t_AST	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = N_HEREDOC;
	cmd->subcmd = subcmd;
	cmd->file = limiter;
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
	cmd->type = N_PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}

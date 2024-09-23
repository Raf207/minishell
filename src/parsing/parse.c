/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:00:24 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/22 01:47:53 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_AST	*ft_parseredir(t_AST *cmd, t_token_list **list)
{
	t_AST		**top;
	t_AST		*temp;
	t_AST		*temp2;

	temp = cmd;
	top = &temp;
	while ((*list) && ((*list)->type == RED_IN || (*list)->type == RED_APPEND
			|| (*list)->type == RED_OUT || (*list)->type == HEREDOC))
	{
		cmd = (*top);
		temp2 = temp;
		while (cmd->type == REDIR || cmd->type == N_HEREDOC)
		{
			temp2 = cmd;
			cmd = cmd->subcmd;
		}
		cmd = ft_addredir(cmd, list);
		if (temp2->subcmd)
			temp2->subcmd = cmd;
		else
			temp = cmd;
		(*list) = (*list)->next;
	}
	return (*top);
}

t_AST	*ft_parseexec(t_token_list **list)
{
	t_AST		*cmd;
	t_AST		*top;
	t_token_typ	tok;

	top = ft_execnode();
	cmd = top;
	top = ft_parseredir(top, list);
	while ((*list) && ((*list)->type != PIPE && (*list)->type != END))
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
	if ((*list) && (*list)->type == PIPE)
	{
		(*list) = (*list)->next;
		cmd = ft_pipenode(cmd, ft_parsepipe(list));
	}
	return (cmd);
}

t_AST	*ft_parsing(t_token_list **list)
{
	t_AST	*cmd;

	cmd = ft_parsepipe(list);
	return (cmd);
}

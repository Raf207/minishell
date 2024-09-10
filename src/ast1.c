/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:57:28 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/10 18:26:10 by rafnasci         ###   ########.fr       */
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

int	ft_findpath(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (i);
	return (-1);
}

t_AST	*ft_execnode(void)
{
	t_AST	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
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
		{
			cmd = ft_redirnode(cmd, (*list)->value, O_RDONLY, 0);
		}
		else if (tok == RED_OUT)
			cmd = ft_redirnode(cmd, (*list)->value,
					O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == RED_APPEND)
			cmd = ft_redirnode(cmd, (*list)->value, O_WRONLY | O_CREAT, 1);
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
		return (NULL);
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


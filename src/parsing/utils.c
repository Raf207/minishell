/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:20:40 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/23 20:44:05 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_findexec(t_AST	*cmd)
{
	t_AST	*tmp;

	tmp = cmd;
	while (tmp->type != EXEC)
		tmp = tmp->subcmd;
	if (tmp->argv)
		return (tmp->argv[0]);
	else
		return (NULL);
}

t_AST	*ft_addredir(t_AST *cmd, t_token_list **list)
{
	t_token_typ	tok;
	char		*file;

	tok = (*list)->type;
	(*list) = (*list)->next;
	if ((*list)->type != WORD)
	{
		ft_printf_fd(1, "minishell: missing file for redirection\n");
		g_exitcode = 258;
	}
	file = ft_strdup((*list)->value);
	if (tok == RED_IN)
		cmd = ft_redirnode(cmd, file, O_RDONLY, 0);
	else if (tok == RED_OUT)
		cmd = ft_redirnode(cmd, file,
				O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (tok == RED_APPEND)
		cmd = ft_redirnode(cmd, file,
				O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (tok == HEREDOC)
		cmd = ft_heredocnode(cmd, file);
	return (cmd);
}

char	**ft_firstargv(char **argv, char *arg)
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

char	**ft_addargv(char **argv, char *arg)
{
	int		nb_args;
	char	**rep;

	if (!argv)
		return (ft_firstargv(argv, arg));
	nb_args = -1;
	while (argv[++nb_args])
		;
	rep = malloc(sizeof(char *) * (nb_args + 2));
	if (!rep)
		return (ft_free(argv), NULL);
	rep[nb_args + 1] = 0;
	rep[nb_args] = ft_strdup(arg);
	if (!rep[nb_args])
		return (ft_free(argv), free(rep), NULL);
	while (--nb_args >= 0)
		rep[nb_args] = argv[nb_args];
	free(argv);
	return (rep);
}

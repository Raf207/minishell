/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:20:40 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/16 21:57:12 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_AST	*ft_addredir(t_AST *cmd, t_token_list **list)
{
	t_token_typ	tok;

	tok = (*list)->type;
	(*list) = (*list)->next;
	if ((*list)->type != WORD)
		ft_panic("missing file for redirection");
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
	else if (tok == HEREDOC)
		cmd = ft_heredocnode(cmd, (*list)->value);
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

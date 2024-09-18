/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:41:32 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/18 21:26:54 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	ft_exit_tokens(t_token_list **tokens)
{
	ft_putendl_fd("malloc", 2);
	ft_cleantoken(tokens);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:54:52 by rafnasci          #+#    #+#             */
/*   Updated: 2024/10/26 21:55:44 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_signal(int signal)
{
	g_minishell.signal = signal;
	g_minishell.heredoc = true;
	set_env(&g_minishell.envs, "?",
		ft_itoa(128 + g_minishell.signal));
}
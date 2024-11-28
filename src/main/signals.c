/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:54:52 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/28 19:30:44 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*ft_boolhere(int i)
{
	static int	boole = 0;

	if (i != 0)
		boole = i;
	return (&boole);
}

void	ft_hered_sig_handler(int sig)
{
	struct termios	term;

	if (sig == SIGINT)
	{
		ft_boolhere(1);
		printf("\n");
		close(STDIN_FILENO);
		g_exitcode = 1;
	}
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &term);
}

void	ft_main_sig_handler(int sig)
{
	struct termios	term;

	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_exitcode = 1;
	}
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &term);
}

void	ft_exec_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exitcode = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_printf_fd(2, "^\\Quit : 3\n");
		g_exitcode = 131;
	}
}

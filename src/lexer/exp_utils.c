/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:36:48 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/29 00:14:16 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\r' || c == '\n'
		|| c == '\f' || c == '\v' || c == '\t');
}

void	ft_checkcoma(char *str, char *c, int i)
{
	static int	coma = 0;

	if (coma == 0 && (str[i] == '\'' || str[i] == '"'))
	{
		*c = str[i];
		coma = 1;
	}
	else if (str[i] == *c && (str[i] == '\'' || str[i] == '"'))
	{
		*c = '0';
		coma = 0;
	}
}

void	ft_findinenv(t_env *start, char *str, int *len, int i)
{
	while (start)
	{
		if (ft_strncmp(start->name, &str[i + 1], ft_len(str, i)) == 0
			&& start->name[ft_len(str, i)] == 0)
		{
			(*len) += ft_strlen(start->value);
			break ;
		}
		start = start->next;
	}
}

int	ft_addexitcode(char *rep, char *str, int i, t_exp *p)
{
	char	*exit_code;

	ft_checkcoma(str, &(p->c), p->i);
	if (p->c != '\'' && str[i] == '$' && str[i + 1] == '?')
	{
		exit_code = ft_itoa(g_exitcode);
		ft_strlcpy(rep, exit_code, ft_strlen(exit_code) + 1);
		p->tot += ft_strlen(exit_code);
		p->i += 1;
		free(exit_code);
		return (1);
	}
	return (0);
}

void	ft_exitcode(int *len)
{
	char	*exit_code;

	exit_code = ft_itoa(g_exitcode);
	(*len) += ft_strlen(exit_code) - 2;
	free(exit_code);
}

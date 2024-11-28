/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:36:48 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/28 06:30:00 by rafnasci         ###   ########.fr       */
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

// void	ft_changeinenv(t_env *start, char *str, char *rep, int i)
// {
// 	while (start)
// 	{
// 		if (ft_strncmp(start->name, &str[i + 1], ft_len(str, i)) == 0
// 			&& start->name[ft_len(str, i)] == 0
// 			&& ft_exputils(rep, start, &tot))
// 			break ;
// 		start = start->next;
// 	}
// 	i += ft_len(str, i);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:36:48 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/28 22:13:32 by rafnasci         ###   ########.fr       */
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

	printf("stc : %c\n",str[i]);
	if (coma == 0 && (str[i] == '\'' || str[i] == '"'))
	{
		printf("yo\n");
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

char	*ft_addexitcode(char *value)
{
	char	*exit_code;
	char	*temp;
	char	*temp2;

	exit_code = ft_itoa(g_exitcode);
	temp2 = ft_strnstr(value, "$?", ft_strlen(value));
	temp = ft_strjoin(ft_substr(value, 0, temp2 - value), exit_code);
	free(exit_code);
	exit_code = value;
	value = ft_strjoin(temp, temp2 + 2);
	free(exit_code);
	return (value);
}

int	ft_isincoma(char *str)
{
	int		i;
	char	c;

	i = -1;
	c = '0';
	while (str[++i])
	{
		ft_checkcoma(str, &c, i);
		printf("c : %c\n", c);
		if (c != '\'' && str[i] == '$' && str[i + 1] == '?')
			return (1);
	}
	printf("---------\n");
	return (0);
}

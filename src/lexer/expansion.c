/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:46:58 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/17 21:50:25 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_len(char	*str, int i)
{
	int	j;

	j = 0;
	while (str[i + j + 1] && !ft_isspace(str[i + j + 1]))
		j++;
	return (j);
}

static int	ft_lenexp(char *str, t_env **env)
{
	int		i;
	int		len;
	t_env	*start;

	i = -1;
	len = ft_strlen(str);
	while (str[++i])
	{
		start = *env;
		if (str[i] == '$')
		{
			len -= ft_len(str, i) + 1;
			while (start)
			{
				if (ft_strncmp(start->name, &str[i + 1], ft_len(str, i)) == 0
					&& start->name[ft_len(str, i)] == 0)
				{
					len += ft_strlen(start->value);
					break ;
				}
				start = start->next;
			}
		}
	}
	return (len);
}

void	ft_newstr(char *str, t_env **env, char	*rep)
{
	int		i;
	int		tot;
	t_env	*start;

	i = -1;
	tot = 0;
	while (str[++i])
	{
		start = *env;
		if (str[i] == '$')
		{
			while (start)
			{
				if (ft_strncmp(start->name, &str[i + 1], ft_len(str, i)) == 0
					&& start->name[ft_len(str, i)] == 0)
				{
					ft_strlcpy(&rep[tot], start->value, ft_strlen(start->value) + 1);
					tot += ft_strlen(start->value);
					break ;
				}
				start = start->next;
			}
			i += ft_len(str, i);
		}
		else
			rep[tot++] = str[i];
	}
}

char *ft_expansion(char *str, t_env **env)
{
	int		i;
	t_env	*start;
	int		tot;
	int		len;
	char	*rep;

	tot = ft_lenexp(str, env);
	rep = malloc(sizeof(char) * (tot + 1));
	rep[tot] = 0;
	i = -1;
	tot = 0;
	while (str[++i])
	{
		start = *env;
		if (str[i] == '$')
		{
			len -= ft_len(str, i) + 1;
			while (start)
			{
				if (ft_strncmp(start->name, &str[i + 1], ft_len(str, i)) == 0
					&& start->name[ft_len(str, i)] == 0)
				{
					ft_strlcpy(&rep[tot], start->value, ft_strlen(start->value) + 1);
					tot += ft_strlen(start->value);
					break ;
				}
				start = start->next;
			}
			i += ft_len(str, i);
		}
		else
			rep[tot++] = str[i];
	}
	return (rep);
}

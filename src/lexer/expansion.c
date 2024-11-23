/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:46:58 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/23 06:19:43 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_len(char	*str, int i)
{
	int	j;

	j = 0;
	while (str[i + j + 1] && !ft_isspace(str[i + j + 1])
		&& str[i + j + 1] != '\'' && str[i + j + 1] != '"'
		&& str[i + j + 1] != '/')
		j++;
	return (j);
}

static int	ft_lenexp(char *str, t_env **env)
{
	int		i;
	int		len;
	t_env	*start;
	int		coma;
	char	c;

	i = -1;
	len = ft_strlen(str);
	coma = 0;
	c = '0';
	while (str[++i])
	{
		start = *env;
		if (coma == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			c = str[i];
			coma = 1;
		}
		else if (str[i] == c && (str[i] == '\'' || str[i] == '"'))
		{
			c = '0';
			coma = 0;
		}
		if (c != '\'' && str[i] == '$' && str[i + 1] != '?'
			&& str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
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
	printf("len : %d\n", len);
	return (len);
}

static int	ft_exputils(char *rep, t_env *start, int *tot)
{
	ft_strlcpy(&rep[(*tot)], start->value, ft_strlen(start->value) + 1);
	(*tot) += ft_strlen(start->value);
	return (1);
}

void	ft_newstr(char *str, t_env **env, char	*rep)
{
	int		i;
	int		tot;
	t_env	*start;
	int		coma;
	char	c;

	coma = 0;
	i = -1;
	tot = 0;
	c = '0';
	while (str[++i])
	{
		start = *env;
		if (coma == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			c = str[i];
			coma = 1;
		}
		else if (str[i] == c && (str[i] == '\'' || str[i] == '"'))
		{
			c = '0';
			coma = 0;
		}
		if (c != '\'' && str[i] == '$' && str[i + 1] != '?'
			&& str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
		{
			while (start)
			{
				if (ft_strncmp(start->name, &str[i + 1], ft_len(str, i)) == 0
					&& start->name[ft_len(str, i)] == 0
					&& ft_exputils(rep, start, &tot))
					break ;
				start = start->next;
			}
			i += ft_len(str, i);
		}
		else
			rep[tot++] = str[i];
	}
}

char	*ft_expansion(char *str, t_env **env)
{
	int		tot;
	char	*rep;

	tot = ft_lenexp(str, env);
	rep = malloc(sizeof(char) * (tot + 1));
	if (!rep)
		return (NULL);
	rep[tot] = 0;
	ft_newstr(str, env, rep);
	free(str);
	printf("rep : %s\n", rep);
	return (rep);
}

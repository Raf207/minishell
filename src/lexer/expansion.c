/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:46:58 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/29 00:14:09 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_len(char	*str, int i)
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
	char	c;

	i = -1;
	len = ft_strlen(str);
	c = '0';
	while (str[++i])
	{
		start = *env;
		ft_checkcoma(str, &c, i);
		if (c != '\'' && str[i] == '$' && str[i + 1] == '?')
			ft_exitcode(&len);
		if (c != '\'' && str[i] == '$' && str[i + 1] != '?' && str[i + 1] != ' '
			&& str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
		{
			len -= ft_len(str, i) + 1;
			ft_findinenv(start, str, &len, i);
		}
	}
	return (len);
}

static int	ft_exputils(char *rep, char *str, t_exp *p, int mode)
{
	if (mode == 0)
	{
		ft_strlcpy(&rep[p->tot], p->en->value, ft_strlen(p->en->value) + 1);
		p->tot += ft_strlen(p->en->value);
		return (1);
	}
	else
		return (p->c != '\'' && str[p->i] == '$' && str[p->i + 1] != '?'
			&& str[p->i + 1] != ' '
			&& str[p->i + 1] != '"' && str[p->i + 1] != '\'' && str[p->i + 1]);
}

void	ft_newstr(char *str, t_env **env, char	*rep)
{
	t_exp	p;

	p.i = -1;
	p.tot = 0;
	p.c = '0';
	while (str[++(p.i)])
	{
		p.en = *env;
		if (ft_addexitcode(&rep[p.tot], str, p.i, &p))
			;
		else if (ft_exputils(rep, str, &p, 1))
		{
			while (p.en)
			{
				if (!ft_strncmp((p.en)->name, &str[p.i + 1], ft_len(str, p.i))
					&& (p.en)->name[ft_len(str, p.i)] == 0
					&& ft_exputils(rep, str, &p, 0))
					break ;
				p.en = (p.en)->next;
			}
			p.i += ft_len(str, p.i);
		}
		else
			rep[(p.tot)++] = str[p.i];
	}
}

char	*ft_expansion(char *str, t_env **env)
{
	int		tot;
	char	*rep;

	if (!str)
		return (NULL);
	tot = ft_lenexp(str, env);
	rep = malloc(sizeof(char) * (tot + 1));
	if (!rep)
		return (NULL);
	ft_newstr(str, env, rep);
	rep[tot] = 0;
	free(str);
	return (rep);
}

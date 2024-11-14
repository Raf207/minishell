/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:34:54 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/13 17:00:18 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_var(char *str, t_env **env)
{
	t_env	*head;
	t_env	*tmp;

	if (*env && !ft_strncmp((*env)->name, str, INT_MAX))
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free_node(tmp);
		return ;
	}
	head = *env;
	while (*env)
	{
		if ((*env)->next && !ft_strncmp((*env)->next->name, str, INT_MAX))
		{
			tmp = (*env)->next;
			(*env)->next = (*env)->next->next;
			free_node(tmp);
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = head;
}

void	unset(char **token, t_env **env)
{
	int	i;

	if (!env || !token[1])
		return ;
	i = 1;
	while (token[i])
	{
		if (!check_identifier(token[i]))
		{
			ft_printf_fd(2, "bash: export: %s: not a valid identifier\n",
				token[i]);
			g_exitcode = 1;
		}
		else
			unset_var(token[i], env);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:34:54 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/10 14:48:42 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while ((*env))
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

void	unset(t_token_list *token, t_env **env)
{
	if (!env || !token->next->value) // if (!env || !token[1]) 
		return ;
	token = token->next; // i = 1;
	while (token->next) //while (token[i]) 
	{
		if (!check_identifier(token->value)) // if (!check_identifier(token[i]))
		{
			ft_printf_fd(2, "bash: unset: %s: not a valid identifier\n",
				token->value); // ft_printf_fd(2, "bash: export: %s: not a valid identifier\n", token[i]); 
			g_exitcode = 1;
		}
		else
			unset_var(token->value, env); // set_var(token[i], env);
		token = token->next; // i++;
	}
}

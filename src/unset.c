/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:34:54 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/04 22:59:19 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_identifier(char *str)
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
// static int	exist(char *str, t_env *env)
//{
//	int		j;
//	t_env	*tmp;

//	if (!env)
//		return (-1);
//	j = 0;
//	tmp = env;
//	while (tmp)
//	{
//		if (!ft_strncmp(tmp->name, str, INT_MAX))
//			return (j);
//		tmp = tmp->next;
//		j++;
//	}
//	return (-1);
//}

static void	unset_var(char *str, t_env **env)
{
	t_env	*head;
    t_env   *tmp;

	// int index;
	// index = exist(str, (*env));
	head = *env;
	while ((*env))
	{
		if (!ft_strncmp((*env)->next->name, str, INT_MAX))
		{
			free_node((*env)->next);
			(*env)->next = (*env)->next->next;
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = head; // free ??
}

void	unset(t_token_list *token, t_env **env)
{
	if (!env || !token->next->value)
		return ;
	token = token->next;
	while (token->next)
	{
		printf("tok : %s\n", token->value);
		if (!check_identifier(token->value))
		{
			ft_printf_fd(2, "bash: unset: %s: not a valid identifier\n",
				token->value);
			g_exitcode = 1;
		}
		else
		{
			unset_var(token->value, env);
		}
		token = token->next;
	}
}

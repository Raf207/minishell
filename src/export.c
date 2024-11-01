/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:12:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/01 17:21:08 by mucabrin         ###   ########.fr       */
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
static int	find_char(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}

static int	exist(char *str, t_env *env)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->name, str, i))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, str, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static void	set_var(char *str, t_env **env)
{
	int		pos;
	int		i;
	int		len;
	char	*value;

	// pos = exist(str, (*env));
	len = find_char(str, '=');
	printf("token : %s\n", str);
	value = ft_substr(str, len + 1, INT_MAX);
	printf("value : %s\n", value);
	// if (!value)
	// 	return ;
	// if (pos >= 0)
	// {
	// 	i = 0;
	// 	while (i < pos)
	// 	{
	// 		(*env) = (*env)->next;
	// 		i++;
	// 	}
	// 	free((*env)->value);
	// 	(*env)->value = value;
	// }
	// else
	// 	printf("append\n");
	// else if (pos == -1)
	// 	append(env, value);
}


void	export(t_token_list *token, t_env **env)
{
	t_env	*export;

	if (!token->next->value)
	{
		sort_env(*env);
		return ;
	}
	token = token->next;
	printf("token : %s\n", token->value);
	// while (token->next)
	// {
	// 	// if (!check_identifier(token->value))
	// 	// {
	// 	// 	ft_printf_fd(2, "bash: export: %s: not a valid identifier\n",
	// 	// 		token->value);
	// 	// 	g_exitcode = 1;
	// 	// 	return ;
	// 	// }
	// 	// else
	// 	// {
	// 		set_var(token->value, env);
	// 	// }
	// 	token = token->next;
		// else if (!export(!token->next->value[i], env))
		// 	return (print_error(ERR_MALLOC));
	// }
}

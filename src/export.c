/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:12:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/07 00:02:08 by mucabrin         ###   ########.fr       */
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

static int	envchr(char *str, t_env *env)
{
	t_env	*tmp;
	int		i;

	if (!env)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
		// len = find_char(str, '=');
	// name = ft_substr(str, 0, len);
	tmp = env;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->name, str, i))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

// static int	exist(char *str, t_env *env)
//{
//	int		i;
//	int		j;
//	t_env	*tmp;

//	if (!env)
//		return (-1);
//	i = 0;
//	//while (str[i] && str[i] != '=')
//	//	i++;
//	j = 0;
//	tmp = env;
//	if (!ft_strncmp(tmp->name, str, i))
//		return (j);
//	tmp = tmp->next;
//	j++;
//	while (tmp)
//	{
//		if (!ft_strncmp(tmp->name, str, i))
//			return (j);
//		tmp = tmp->next;
//		j++;
//	}
//	return (-1);
//}

// static int	exist(char *str, t_env *env)
// {
// 	int		j;
// 	t_env	*tmp;

// 	if (!env)
// 		return (-1);
// 	j = 0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->name, str, INT_MAX))
// 			return (j);
// 		tmp = tmp->next;
// 		j++;
// 	}
// 	return (-1);
// }

static int	findo(const char *str, int c)
{
	int	i;

	i = 0;
	printf("str %s\n", str);
	while (str[i])
	{
		printf("c %c\n", str[i]);
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	set_value(char *str, t_env **env)
{
	int		len;
	char	*name;
	char	*value;
	t_env	*top;

	len = find_char(str, '=');
	name = ft_substr(str, 0, len);
	value = ft_substr(str, len + 1, INT_MAX);
	// if (!value)
	//	return ;
	top = *env;
	// printf("str %s\n", str);
	// printf("findo %d\n", findo(str, ''=));
	while ((*env))
	{
		if (!ft_strncmp((*env)->name, name, INT_MAX) && ft_strchr(str, '='))
		{
			free((*env)->value);
			(*env)->value = value;
			if (!ft_strchr(str, '='))
			{
				(*env)->equal = false;
				printf("false\n");
			}
			else
			{
				(*env)->equal = true;
				printf("true\n");
			}
			printf("name %s | value %s | equal %d \n", (*env)->name,
				(*env)->value, (*env)->equal);
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = top;
	// check first elem
}

static void	set_var(char *str, t_env **env)
{
	t_env	*top;

	// top = *env;
	// len = find_char(str, '=');
	// name = ft_substr(str, 0, len);
	if (envchr(str, *env))
		set_value(str, *env);
	else
		append_list(env, str);
	//*env = top; // free ??
	printf("OK\n");
}

void	export(t_token_list *token, t_env **env)
{
	t_env	*export;
	t_env	*top;

	if (!token->next->value)
	{
		sort_env(*env);
		return ;
	}
	token = token->next;
	// printf("token : %s\n", token->value);
	while (token->next)
	{
		if (!check_identifier(token->value))
		{
			ft_printf_fd(2, "bash: export: %s: not a valid identifier\n",
				token->value);
			g_exitcode = 1;
		}
		else
		{
			set_var(token->value, env);
		}
		token = token->next;
		// else if (!export(!token->value, env))
		// 	return (print_error);
	}
	printf("end\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:12:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/04 22:59:55 by mucabrin         ###   ########.fr       */
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
static int envchr(char *name, t_env *env)
{
	t_env *tmp;
	if (!env)
		return (0);
	tmp = env;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->name, name, INT_MAX))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
//static int	exist(char *str, t_env *env)
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

static int	exist(char *str, t_env *env)
{
	int		j;
	t_env	*tmp;

	if (!env)
		return (-1);
	j = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, str, INT_MAX))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

// void	append(char *name, char *value, t_env **env, t_env *head)
// {
// 	t_env *new_node;
	
// 	*env = head;
// 	new_node = malloc(sizeof(t_env));
// 		if (!new_node)
// 			return (NULL);
// 	new_node->name = ft_strdup(name);
// 	new_node->value = ft_strdup(value);
// 	new_node->next = NULL;
// 	while ((*env)->next)
// 		env = (*env)->next;
// 	(*env)->next = new_node;
// }


static void	set_var(char *str, t_env **env)
{
	t_env	*top;
	t_built var;

	var.len = find_char(str, '=');
	var.name = ft_substr(str, 0, var.len);
	var.value = ft_substr(str, var.len + 1, INT_MAX);
	if (!var.value)
		return ;
	top = *env;
	if (envchr(var.name, *env))
	{
		while ((*env))
		{
			if (!ft_strncmp((*env)->name, var.name, INT_MAX))
			{
				free((*env)->value);
				(*env)->value = var.value;
				break ;
			}
			(*env) = (*env)->next;
		}
	}
	else
		append_list(env, str);
	*env = top; // free ??
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

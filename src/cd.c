/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:07:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/10 14:38:37 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_findnode(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, INT_MAX) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd_error(t_env **env, t_built *var)
{
	var->dir = opendir(var->path);
	var->env_oldpwd = ft_findnode(*env, "OLDPWD");
	var->env_pwd = ft_findnode(*env, "PWD");
	var->env_home = ft_findnode(*env, "HOME");
	if (var->path && !var->dir && !diff_dir(var->path))
	{
		if (errno)
		{
			ft_printf_fd(2, "bash: cd: %s: %s\n", var->path, strerror(errno));
			g_exitcode = 1;
			return ;
		}
	}
}

void	cd(t_token_list *token, t_env **env)
{
	t_built	var;

	var.path = token->next->value; // ft_strdup(token[1]);
	if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
		var.path = token->next->next->value; // ft_strdup(token[2]);
	else if (token->next->next->value) // else if (token[2])
	{
		ft_printf_fd(2, "bash: cd: too many arguments\n");
		g_exitcode = 1;
		return ;
	}
	cd_error(env, &var);
	if (!var.path || ft_strncmp(var.path, "~", INT_MAX) == 0
		|| ft_strncmp(var.path, "#", INT_MAX) == 0)
		cd_home(env, &var);
	else if (ft_strncmp(var.path, "-", INT_MAX) == 0)
		cd_oldpwd(env, &var);
	else
		cd_dir(env, &var);
}

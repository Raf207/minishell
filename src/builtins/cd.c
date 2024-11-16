/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:07:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/16 19:17:26 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	cd_error(t_env **env, t_built *var)
{
	var->dir = opendir(var->path);
	var->env_oldpwd = ft_findnode(*env, "OLDPWD");
	var->env_pwd = ft_findnode(*env, "PWD");
	var->env_home = ft_findnode(*env, "HOME");
	if (var->path && !var->dir && !diff_dir(var->path))
	{
		ft_printf_fd(2, "bash: cd: %s: %s\n", var->path, strerror(errno));
		g_exitcode = 1;
		return (0);
	}
	if (var->dir)
		closedir(var->dir);
	return (1);
}

void	cd(char **token, t_env **env)
{
	t_built	var;

	var.path = token[1];
	if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
		var.path = token[2];
	else if (var.path && token[2])
	{
		ft_printf_fd(2, "bash: cd: too many arguments\n");
		g_exitcode = 1;
		return ;
	}
	if (!cd_error(env, &var))
		return ;
	if (!var.path || ft_strncmp(var.path, "~", INT_MAX) == 0
		|| ft_strncmp(var.path, "#", INT_MAX) == 0)
		cd_home(&var);
	else if (ft_strncmp(var.path, "-", INT_MAX) == 0)
		cd_oldpwd(&var);
	else
		cd_dir(&var);
}

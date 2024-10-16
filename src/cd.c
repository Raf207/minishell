/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:07:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/16 14:51:59 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_findnode(t_env *env, char *name)
{
	int	i;

	i = -1;
	while (env)
	{
		if (ft_strncmp(env->name, name, INT_MAX) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	cd(t_token_list *token, t_env **env)
{
	t_cd	var;

	var.path = token->next->value;
	if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
		var.path = token->next->next->value;
	var.dir = opendir(var.path);
	var.env_oldpwd = ft_findnode(*env, "OLDPWD");
	var.env_pwd = ft_findnode(*env, "PWD");
	var.env_home = ft_findnode(*env, "HOME");
	if (var.path && !var.dir && !diff_dir(var.path))
	{
		if (errno)
		{
			ft_printf_fd(2, "bash: cd: %s: %s\n", var.path, strerror(errno));
			g_exitcode = 1;
			return ;
		}
	}
	if (!var.path || ft_strncmp(var.path, "~", INT_MAX) == 0
		|| ft_strncmp(var.path, "#", INT_MAX) == 0)
		cd_home(env, &var);
	else if (ft_strncmp(var.path, "-", INT_MAX) == 0)
		cd_oldpwd(env, &var);
	else
		cd_dir(env, &var);
}

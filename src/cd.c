/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:07:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/07 21:22:38 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_findnode(t_env *env, char *name)
{
	t_env	*tmp;
	printf("check 2\n");
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, INT_MAX) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd(t_token_list *token, t_env **env)
{
	t_built	var;

	var.path = token->next->value;
	if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
		var.path = token->next->next->value;
	var.dir = opendir(var.path);
	var.env_oldpwd = ft_findnode(*env, "OLDPWD");
	var.env_pwd = ft_findnode(*env, "PWD");
	printf("check 1\n");
	//if (!var.env_pwd)
	//{
	//	var.env_pwd = malloc(sizeof(t_env));
	//	var.env_pwd->value = getcwd(NULL, 0);
	//}
	var.env_home = ft_findnode(*env, "HOME");
	printf("check 2\n");
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

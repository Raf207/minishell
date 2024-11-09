/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:08:05 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/09 23:38:21 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	new_cd_dir(t_env **env, t_built *var)
// {
// 	char	*pwd;
// 	char	*oldpwd;

// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 	{
// 		ft_printf_fd(STDERR_FILENO,
// 			"pwd: error retrieving current directory: getcwd: cannot");
// 		ft_printf_fd(STDERR_FILENO,
// 			" access parent directories: No such file or directory\n");
// 		return ;
// 	}
// 	oldpwd = pwd;
// 	chdir(var->path);
// 	if (!var->env_pwd && var->env_oldpwd)
// 	{
// 		free(var->env_oldpwd->value);
// 		var->env_oldpwd->value = ft_strdup(oldpwd);
// 	}
// 	else if (var->env_pwd && !var->env_oldpwd)
// 	{
// 	}
// }

void	cd_dir(t_env **env, t_built *var)
{
	// if (!var->env_pwd || !var->env_home || !var->env_oldpwd)
	// 	new_cd_dir(env, &var);
	if (var->env_oldpwd)
	{
		free(var->env_oldpwd->value);
		if (var->env_pwd)
			var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
		else
			var->env_oldpwd->value = getcwd(NULL, 0);
	}
	chdir(var->path);
	if (var->env_pwd)
	{
		if (!getcwd(NULL, 0))
		{
			ft_printf_fd(STDERR_FILENO,
				"cd: error retrieving current directory: getcwd: cannot");
			ft_printf_fd(STDERR_FILENO,
				" access parent directories: No such file or directory\n");
			var->env_pwd->value = ft_strjoin(var->env_pwd->value, "/..");
		}
		else
			var->env_pwd->value = getcwd(NULL, 0);
	}
}

void	cd_oldpwd(t_env **env, t_built *var)
{
	if (!var->env_oldpwd || !var->env_oldpwd->value)
	{
		printf("bash: cd: OLDPWD not set\n");
		g_exitcode = 1;
		return ;
	}
	var->tmp = var->env_oldpwd->value;
	if (chdir(var->tmp) < 0)
	{
		ft_printf_fd(STDERR_FILENO, "bash: cd: %s: %s\n", var->tmp,
			strerror(errno));
		g_exitcode = 1;
		return ;
	}
	// free(var->env_oldpwd->value);
	var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
	var->env_pwd->value = getcwd(NULL, 0);
	printf("%s\n", var->tmp);
}

void	cd_home(t_env **env, t_built *var)
{
	if (!ft_strncmp(var->path, "~", INT_MAX) && !var->env_home)
	{
		var->path = getenv("HOME");
		printf("getenv : %s\n", var->path);
	}
	else if (!var->env_home)
	{
		ft_printf_fd(2, "bash: cd: HOME not set\n");
		g_exitcode = 1;
		return ;
	}
	if (var->env_oldpwd)
	{
		free(var->env_oldpwd->value);
		if (var->env_pwd)
			var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
		else
			var->env_oldpwd->value = getcwd(NULL, 0);
	}
	if (var->env_pwd)
	{
		free(var->env_pwd->value);
		if (var->env_home)
			var->env_pwd->value = ft_strdup(var->env_home->value);
		else
			var->env_pwd->value = ft_strdup(var->path);
		printf("name : %s value : %s\n", var->env_pwd->name, var->env_pwd->value);
		chdir(var->env_pwd->value);
	}
	else
		if (var->env_home)
			chdir(var->env_home->value);
		else
			chdir(var->path);
}

int	diff_dir(const char *path)
{
	return (NULL || ft_strncmp(path, "~", INT_MAX) == 0 || ft_strncmp(path, "#",
			INT_MAX) == 0 || ft_strncmp(path, "-", INT_MAX) == 0);
}

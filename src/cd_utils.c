/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:08:05 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/16 13:08:06 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd_dir(t_env **env, t_cd *var)
{
	free(var->env_oldpwd->value);
	var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
	chdir(var->path);
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

void	cd_oldpwd(t_env **env, t_cd *var)
{
	if (var->env_oldpwd->value == NULL)
	{
		g_exitcode = 1;
		printf("bash: cd: OLDPWD not set\n");
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

void	cd_home(t_env **env, t_cd *var)
{
	free(var->env_oldpwd->value);
	var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
	free(var->env_pwd->value);
	var->env_pwd->value = ft_strdup(var->env_home->value);
	printf("name : %s value : %s\n", var->env_pwd->name, var->env_pwd->value);
	chdir(var->env_pwd->value);
}

int	diff_dir(const char *path)
{
	return (NULL || ft_strncmp(path, "~", INT_MAX) == 0 || ft_strncmp(path, "#",
			INT_MAX) == 0 || ft_strncmp(path, "-", INT_MAX) == 0);
}

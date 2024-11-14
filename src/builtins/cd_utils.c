/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:08:05 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/14 16:49:33 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_dir(t_built *var)
{
	char	*tmp;

	if (var->env_oldpwd)
	{
		free(var->env_oldpwd->value);
		if (var->env_pwd)
			var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
		else
			var->env_oldpwd->value = getcwd(NULL, 0);
	}
	chdir(var->path);
	if (!var->env_pwd)
		return ;
	tmp = var->env_pwd->value;
	free(var->env_pwd->value);
	var->env_pwd->value = getcwd(NULL, 0);
	if (var->env_pwd->value)
		return ;
	ft_printf_fd(STDERR_FILENO,
		"cd: error retrieving current directory: getcwd: cannot");
	ft_printf_fd(STDERR_FILENO,
		" access parent directories: No such file or directory\n");
	var->env_pwd->value = ft_strjoin(tmp, "/..");
}

void	cd_oldpwd(t_built *var)
{
	if (!var->env_oldpwd || !var->env_oldpwd->value
		|| !var->env_oldpwd->value[0])
	{
		printf("bash: cd: OLDPWD not set\n");
		g_exitcode = 1;
		return ;
	}
	var->tmp = getcwd(NULL, 0);
	if (chdir(var->env_oldpwd->value) < 0)
	{
		g_exitcode = 1;
		return (ft_printf_fd(2, "bash: cd: %s: %s\n", var->env_oldpwd->value,
				strerror(errno)), free(var->tmp));
	}
	printf("%s\n", var->env_oldpwd->value);
	free(var->env_oldpwd->value);
	if (var->env_pwd)
	{
		var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
		free(var->env_pwd->value);
		var->env_pwd->value = getcwd(NULL, 0);
	}
	else
		var->env_oldpwd->value = ft_strdup(var->tmp);
	free(var->tmp);
}

static int	cd_homecheck(t_built *var)
{
	if (!ft_strncmp(var->path, "~", INT_MAX) && !var->env_home)
		var->path = getenv("HOME");
	else if (!var->env_home)
	{
		ft_printf_fd(2, "bash: cd: HOME not set\n");
		g_exitcode = 1;
		return (0);
	}
	return (1);
}

void	cd_home(t_built *var)
{
	if (!cd_homecheck(var))
		return ;
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

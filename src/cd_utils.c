#include "../include/minishell.h"

void	cd_home(t_env **env, t_cd *var)
{
	free(var->env_oldpwd->value);
	var->env_oldpwd->value = ft_strdup(var->env_pwd->value);
	free(var->env_pwd->value);
	var->env_pwd->value = ft_strdup(var->env_home->value);
	printf("name : %s value : %s\n", var->env_pwd->name, var->env_pwd->value);
	chdir(var->env_pwd->value);
}

// int	diff_dir(const char *path)
//{
//	return (NULL || ft_strncmp(path, "~", INT_MAX) == 0 || ft_strncmp(path, "#",
//			INT_MAX) == 0 || ft_strncmp(path, "$", INT_MAX) == 0
				//|| ft_strncmp(path,
//			"-", INT_MAX) == 0 || ft_strncmp(path, "--", INT_MAX) == 0);
//}
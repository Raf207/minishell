#include "../include/minishell.h"
#include <sys/stat.h>

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
//
//{
//	return (NULL || ft_strncmp(path, "~", INT_MAX) == 0 || ft_strncmp(path, "#",
//			INT_MAX) == 0 || ft_strncmp(path, "$", INT_MAX) == 0
//		|| ft_strncmp(path, "-", INT_MAX) == 0 || ft_strncmp(path, "--",
//			INT_MAX) == 0);
//}
//

void	cd(t_token_list *token, t_env **env)
{
	t_cd	var;

	var.path = token->next->value;
	if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
	{
		var.path = token->next->next->value;
		printf("path = %s\n", var.path);
	}
	var.dir = opendir(var.path);
	var.env_oldpwd = ft_findnode(*env, "OLDPWD");
	var.env_pwd = ft_findnode(*env, "PWD");
	var.env_home = ft_findnode(*env, "HOME");
	if (var.path && !var.dir && !diff_dir(var.path))
	{
		printf("var.path : %s errno = %d\n", var.path, errno);
		if (errno)
		{
			ft_printf_fd(STDERR_FILENO, "bash: cd: %s: %s\n", var.path,
				strerror(errno));
			g_exitcode = 1;
			return ;
		}
	}
	if (!var.path || ft_strncmp(var.path, "~", INT_MAX) == 0
		|| ft_strncmp(var.path, "#", INT_MAX) == 0)
	{
		cd_home(env, &var);
	}
	else if (ft_strncmp(var.path, "-", INT_MAX) == 0)
	{
		cd_oldpwd(env, &var);
	}
	else
	{
		cd_dir(env, &var);
	}
}

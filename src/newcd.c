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

int	diff_dir(const char *path)
{
	return (NULL || ft_strncmp(path, "~", INT_MAX) == 0 || ft_strncmp(path, "#",
			INT_MAX) == 0 || ft_strncmp(path, "$", INT_MAX) == 0
		|| ft_strncmp(path, "-", INT_MAX) == 0 || ft_strncmp(path, "--",
			INT_MAX) == 0);
}

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
	//	else if (ft_strncmp(path, "-", INT_MAX) == 0)
	//	{
	//		if (env_oldpwd->value == NULL)
	//		{
	//			g_exitcode = 1;
	//			printf("bash: cd: OLDPWD not set\n");
	//			return ;
	//		}
	//		tmp = env_oldpwd->value;
	//		// free(env_oldpwd->value);
	//		env_oldpwd->value = ft_strdup(env_pwd->value);
	//		chdir(tmp);
	//		env_pwd->value = getcwd(NULL, 0);
	//		printf("%s\n", tmp);
	//	}
	//	else
	//	{
	//		if (!getcwd(NULL, 0))
	//		{
	//			ft_printf_fd(STDERR_FILENO,
	//				"cd: error retrieving current directory: getcwd: cannot");
	//			ft_printf_fd(STDERR_FILENO,
	//				"access parent directories: No such file or directory\n");
	//		}
	//		free(env_oldpwd->value);
	//		env_oldpwd->value = ft_strdup(env_pwd->value);
	//		chdir(path);
	//		env_pwd->value = getcwd(NULL, 0);
	//	}
}

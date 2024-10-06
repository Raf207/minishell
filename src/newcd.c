#include "../include/minishell.h"
#include <sys/stat.h>

// int	errno_checker(int error, const char *path)
//{
//	if (error)
//	{
//		ft_printf_fd(STDERR_FILENO, "bash: cd: %s: %s\n", path,
//			strerror(error));
//	}
//	// else if (error == 13)
//	//{
//	//	printf("bash: cd: %s: Permission denied\n", path);
//	//	return (1);
//	//}
//	// else if (error == 20)
//	//{
//	//	printf("bash: cd: %s: Not a directory\n", path);
//	//	return (1);
//	//}
//	// else if (error == 36)
//	//{
//	//	printf("bash: cd: %s: File name too long\n", path);
//	//	return (1);
//	//}
//	return (0);
//}

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
	return (NULL || strncmp(path, "~", INT_MAX) == 0 || strncmp(path, "#",
			INT_MAX) == 0 || strncmp(path, "$", INT_MAX) == 0 || strncmp(path,
			"-", INT_MAX) == 0 || strncmp(path, "--", INT_MAX) == 0);
}

void	cd(t_token_list *token, t_env **env)
{
	const char	*path;
	t_env		*env_oldpwd;
	t_env		*env_pwd;
	char		*tmp;
	t_env		*envpath;

	// struct stat	buffer;
	// int			status;
	// path = token->next->value;
	// status = stat (ft_strjoin(path, "/"), &buffer);
	// if (status < 0)
	//	errno_checker(errno, path);
	// printf("status = %d errno = %d\n", status, errno);
	env_oldpwd = ft_findnode(*env, "OLDPWD");
	env_pwd = ft_findnode(*env, "PWD");
	envpath = ft_findnode(*env, "HOME");
	path = token->next->value;
	if (path && chdir(path) == -1 && !diff_dir(path))
	{
		printf("path : %s errno = %d\n", path, errno);
		if (errno)
		{
			ft_printf_fd(STDERR_FILENO, "bash: cd: %s: %s\n", path,
				strerror(errno));
			g_exitcode = 1;
			return ;
		}
	}
	if (!path || strncmp(path, "~", INT_MAX) == 0 || strncmp(path, "#",
			INT_MAX) == 0 || strncmp(path, "$", INT_MAX) == 0)
	{
		free(env_oldpwd->value);
		env_oldpwd->value = ft_strdup(env_pwd->value);
		free(env_pwd->value);
		env_pwd->value = ft_strdup(envpath->value);
		printf("name : %s value : %s\n", env_pwd->name, env_pwd->value);
		chdir(env_pwd->value);
	}
	else if (strncmp(path, "-", INT_MAX) == 0)
	{
		if (env_oldpwd->value == NULL)
		{
			g_exitcode = 1;
			printf("bash: cd: OLDPWD not set\n");
			return ;
		}
		tmp = env_oldpwd->value;
		free(env_oldpwd->value);
		env_oldpwd->value = ft_strdup(env_pwd->value);
	}
}

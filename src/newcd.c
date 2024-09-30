#include "../include/minishell.h"

int	errno_checker(int error, const char *path)
{
	if (error == 2)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	else if (error == 13)
	{
		printf("bash: cd: %s: Permission denied\n", path);
		return (1);
	}
	else if (error == 20)
	{
		printf("bash: cd: %s: Not a directory\n", path);
		return (1);
	}
	return (0);
}

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
// int	diff_dir(void)
//{

//}

void	cd(t_token_list *token, t_env **env)
{
	const char	*path;
	t_env		*env_oldpwd;
	t_env		*env_pwd;
	char		*tmp;
	int			fd;
	int			fd2;
	DIR			*dir;

	env_oldpwd = ft_findnode(*env, "OLDPWD");
	env_pwd = ft_findnode(*env, "PWD");
	path = token->next->value;

	fd = chdir(path);
	if (fd == -1)
	{
		printf("chdir : Error Number: %d\n", errno);
		perror("Error Description:");
	}
	else
	{
		printf("chdir: No error\n");
	}
	fd2 = access(path, F_OK);
	if (fd2 == -1)
	{
		printf("access : Error Number: %d\n", errno);
		perror("Error Description:");
	}
	else
	{
		printf("access : No error\n");
	}
	dir = opendir(path);
	if (!dir)
	{
		printf("opendir : Error Number: %d\n", errno);
		perror("Error Description:");
	}
	else
	{
		printf("opendir : No error\n");
	}
	//if (chdir(path) == -1)
	//{
	//	if (errno_checker(errno, path))
	//	{
	//		g_exitcode = 1;
	//		return ;
	//	}
		// if (diff_dir(path))
		//{
		//}
	//}
}

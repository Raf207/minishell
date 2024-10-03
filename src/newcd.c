#include "../include/minishell.h"
#include <sys/stat.h>

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
	else if (error == 20)
	{
		printf("bash: cd: %s: \n", path);
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

int	diff_dir(const char *path)
{
	return (strncmp(path, "~", INT_MAX) == 0 || strncmp(path, "#", INT_MAX) == 0
		|| strncmp(path, "-", INT_MAX) == 0 || strncmp(path, "--",
			INT_MAX) == 0);
}

void	cd(t_token_list *token, t_env **env)
{
	const char	*path;
	t_env		*env_oldpwd;
	t_env		*env_pwd;
	char		*tmp;
	struct stat buffer;
	int         status;

	path = token->next->value;
	status = stat (ft_strjoin(path, "/"), &buffer);
	if (status < 0)
		errno_checker(errno, path);
	printf("status = %d errno = %d\n", status, errno);

	//env_oldpwd = ft_findnode(*env, "OLDPWD");
	//env_pwd = ft_findnode(*env, "PWD");
	//path = token->next->value;
	if (chdir(path) == -1)
	{
		printf("path : %s errno = %d\n",path, errno);
		if (errno_checker(errno, path))
		{
			g_exitcode = 1;
			return ;
		}
	}
	//printf("check\n");
}

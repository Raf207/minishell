#include "../include/minishell.h"

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

void	newcd(t_token_list *token, t_env **env)
{
	const char	*path;
	t_env		*envpath;
	t_env		*env_oldpwd;
	t_env		*env_pwd;
	char *tmp;
	const char		*oldpwd;
	const char			*pwd;
	int fd = 0; // access
	DIR *dir;
	// if (!oldpwd)
	//{
	//	oldpwd = getcwd(NULL, 0);
	//}
	envpath = ft_findnode(*env,"HOME");
	env_oldpwd = ft_findnode(*env, "OLDPWD");
	env_pwd = ft_findnode(*env, "PWD");
	printf("name : %s value : %s\n", env_pwd->name, env_pwd->value);
	path = token->next->value;
	 dir = opendir(path);
	 if (!dir)
		printf("fd bash: cd: %s: No such file or directory\n", path);
	//{
	// printf("name : %s value : %s\n", env_oldpwd->name, env_oldpwd->value);
	// newpwd = getcwd(NULL, 0);
	// printf("env_oldpwd before chdir: %s\n", env_oldpwd);
	if (!path || ft_strncmp(path, "~", INT_MAX) == 0)
	{
		free(env_oldpwd->value);
		env_oldpwd->value = getcwd(NULL, 0);
		free(env_pwd->value);
		env_pwd->value = ft_strdup(envpath->value);
		//system("leaks minishell");
		//if (env_pwd->value == NULL)
		//	????
		printf("name : %s value : %s\n", env_pwd->name, env_pwd->value);
		fd = chdir(env_pwd->value);
	}
	else if (ft_strncmp(path, "-", INT_MAX) == 0)
	{
		if (env_oldpwd->value == NULL)
		{
			g_exitcode = 1;
			printf("bash: cd: OLDPWD not set\n");
			return ;
		}
		tmp = env_oldpwd->value;
		//free(env_oldpwd->value); ????
		env_oldpwd->value = getcwd(NULL, 0);
		 fd = chdir(tmp);
		 env_pwd->value = getcwd(NULL, 0);
		 printf("-name : %s -value : %s\n", env_oldpwd->name, env_oldpwd->value);
		 printf("newname : %s newvalue : %s\n", env_pwd->name, env_pwd->value);
		// printf("env_oldpwd 2: %s\n", env_oldpwd);
	}
	else
	{
		free(env_oldpwd->value);
		env_oldpwd->value = getcwd(NULL, 0);
		printf("name : %s value : %s\n", env_oldpwd->name, env_oldpwd->value);
		fd = chdir(path);
		env_pwd->value = getcwd(NULL, 0);
		printf("%s\n", env_pwd->value);
	}
	fd = chdir(path);
	if (fd < 0)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		printf("%d\n", errno); // do a errno function
	}
	// printf("path %s\n", path);
	// printf("newpwd affd chdir: %s\n", newpwd);
	//}
}
// cd -- X

// cd ~USERNAME
// cd ../ rm dir if env_pwd = NULL == error but check with unset too

/* after rm dir: if (cd ..) == cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
 if (cd then cd -) == bash: cd: /Users/mucabrin/MYgoinfre/minishell/test/test1/..: No such file or directory */

// if cd ~mucabrin || #mucabrin || $mucabrin == HOME
// if unset home cd || #mucabrin || $mucabrin == bash: cd: HOME not set, but "~mucabrin" && "cd - || ~" &&  work



// status not good with permission
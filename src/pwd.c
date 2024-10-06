
#include "../include/minishell.h"

void	pwd(t_env **env)
{
	char	*pwd;
	char	*tmp;


	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	//tmp = getcwd(NULL, 0);
	//if(pwd)
	//free
	//pwd = ft_findnode(*env, "PWD");
	//printf("name : [%s] value : %s\n", pwd->name, pwd->value);
	//if (!pwd->value)
	//	pwd->value = getcwd(NULL, 0);
	//printf("%s\n", pwd->value);
	//printf("%s\n", tmp);
}

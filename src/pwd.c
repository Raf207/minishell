
#include "../include/minishell.h"

void	pwd(t_env **env)
{
	char	*pwd;
	t_env	*tmp;


	pwd = getcwd(NULL, 0);
	tmp = ft_findnode(*env, "PWD");
	if(!pwd)
		pwd = tmp->value;
	printf("name : [%s] value : %s\n", tmp->name, tmp->value);
	printf("%s\n", pwd);
}

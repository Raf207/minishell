#include "../include/minishell.h"

int	ft_builtins(t_token_list *token, t_env **env) // t_env env
{
	t_env *node;

	node = env;
	if (ft_strncmp(token->value, "cd", INT_MAX) == 0)
	{
		cd(token, env);
		return (0);
	}
	else if (ft_strncmp(token->value, "pwd", INT_MAX) == 0)
	{
		pwd();
		return (0);
	}
	else if (ft_strncmp(token->value, "env", INT_MAX) == 0)
	{

	}
	else
		printf("NOT YET\n");
	return (1);
}


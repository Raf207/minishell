#include "../include/minishell.h"

int	ft_builtins(t_token_list *token) // t_env env
{
	if (ft_strncmp(token->value, "cd", INT_MAX) == 0)
		cd(token);
	else if (ft_strncmp(token->value, "pwd", INT_MAX) == 0)
		pwd();
	else
		printf("ERROR\n");
	return (0);
}


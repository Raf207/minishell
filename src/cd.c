#include "../include/minishell.h"

void	cd(t_token_list *token)
{
	static const char	*oldpwd;
	const char			*newpwd;
	const char			*path;

	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	path = token->next->value;
	printf("oldpwd before chdir: %s\n", oldpwd);
	if (!path || strncmp(path, "~", INT_MAX) == 0)
	{
		chdir(getenv("HOME"));
		printf("path %s\n", path);
	}
	else if (strncmp(path, "-", INT_MAX) == 0)
	{
		path = oldpwd;
		chdir(path);
	}
	else
		chdir(path);
	// printf("path %s\n", path);
	newpwd = getcwd(NULL, 0);
	printf("newpwd after chdir: %s\n", newpwd);
}

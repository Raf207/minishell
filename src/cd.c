#include "../include/minishell.h"

void	cd(t_token_list *token)
{
	static const char	*oldpwd;
	const char			*newpwd;
	const char			*path;
	int					er;

	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	path = token->next->value;
	printf("oldpwd before chdir: %s\n", oldpwd);
	if (!path || strncmp(path, "~", INT_MAX) == 0)
		er = chdir(getenv("HOME"));
	else if (strncmp(path, "-", INT_MAX) == 0)
	{
		path = oldpwd;
		er = chdir(path);
	}
	else
		er = chdir(path);
	if (er < 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		exit(1);
	}
	else 
		exit(0);
	 printf("path %s\n", path);
	newpwd = getcwd(NULL, 0);
	printf("newpwd after chdir: %s\n", newpwd);
}

#include "../include/minishell.h"

int	cd(t_token_list *token)
{
	static const char	*oldpwd;
	const char			*newpwd;
	const char			*path;
	int					fd;

	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	path = token->next->value;
	printf("oldpwd before chdir: %s\n", oldpwd);
	if (!path || strncmp(path, "~", INT_MAX) == 0)
		fd = chdir(getenv("HOME"));
	else if (strncmp(path, "-", INT_MAX) == 0)
	{
		path = oldpwd;
		fd = chdir(path);
	}
	else
		fd = chdir(path);
	if (fd < 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		exit(1);
	}
	else
		return(0);
	printf("path %s\n", path);
	newpwd = getcwd(NULL, 0);
	printf("newpwd affd chdir: %s\n", newpwd);
		return (0);
}

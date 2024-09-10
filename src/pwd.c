
#include "../include/minishell.h"

void pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}

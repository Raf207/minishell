/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:53:03 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/12 18:57:43 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_env **env)
{
	char	*pwd;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = ft_findnode(*env, "PWD");
	if (!pwd)
	{
		if (!tmp)
		{
			ft_printf_fd(STDERR_FILENO,
				"pwd: error retrieving current directory: getcwd: cannot");
			ft_printf_fd(STDERR_FILENO,
				" access parent directories: No such file or directory\n");
			return ;
		}
		pwd = tmp->value;
		printf("%s\n", pwd);
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}
/* In Bash, the `pwd` (print working directory) command relies on the underlying system call `getcwd()` to retrieve the current working directory.

If `getcwd()` fails and returns `NULL`, this typically indicates an error, such as a failure to access the filesystem or if the current directory has been deleted or is no longer accessible. 

Here’s how Bash behaves in this scenario:

### When `getcwd()` returns `NULL`:
1. **System Call Failure**: `getcwd()` will return `NULL` if there is an error, such as:
   - The current working directory no longer exists.
   - There are permission issues preventing access to the directory.
   - The path exceeds the buffer size allocated for the result.

2. **Error Handling**: When `getcwd()` returns `NULL`, the standard error (`stderr`) is set to a value indicating what went wrong. Bash, when running `pwd`, would detect this error.

3. **Bash's Response**:
   - Bash will display an error message similar to:
     ```
     pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
     ```
   - The return value of the `pwd` command will be a non-zero exit status (indicating failure).

4. **Workaround in Bash**: If Bash cannot determine the working directory, it might still attempt to use a fallback mechanism. For instance:
   - If Bash cannot `getcwd()`, it may rely on a cached value of the current directory (if it's still valid), or it might not be able to print the working directory at all.
   - If no current directory is available, Bash may default to the root directory `/` or an internal value depending on the shell environment.

5. **Why It Happens**:
   - This can happen if the directory you're currently in gets deleted, or if there's some other filesystem-related issue. For example, if you're inside a mount point or directory that has become inaccessible or has been unmounted.

In general, when `getcwd()` fails, Bash tries to report the issue rather than silently failing or printing an incomplete result. The primary issue is a loss of access to the current directory, which is generally indicative of a filesystem or system-level problem. */
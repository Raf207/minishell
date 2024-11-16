/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:53:03 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/16 17:04:16 by mucabrin         ###   ########.fr       */
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

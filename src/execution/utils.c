/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:19:17 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/23 06:52:28 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



int	ft_heredoc_input(int fd, char *limiter)
{
	char	*line;
	int		*handle_ctlc;

	while (1)
	{
		signal(SIGINT, ft_hered_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		handle_ctlc = ft_boolhere(0);
		line = get_next_line(0);
		if (!line && (*handle_ctlc) == 1)
			break ;
		else if (!line)
			return (1);
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& (line[ft_strlen(limiter)] == '\n'))
			return (close(fd), free(line), 1);
		ft_putstr_fd(line, fd);
		free(line);
	}
	ft_boolhere(3);
	return (0);
}

int	ft_findenv(char **envp, char *name)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(name, envp[i], 4) == 0)
			return (i);
	return (-1);
}

void	ft_execution(char **cmd, char **envp)
{
	char	*path_envp;
	char	**all_paths;
	int		i;
	char	*path;

	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	path_envp = ft_substr(envp[ft_findenv(envp, "PATH")], 5, 4654654);
	all_paths = ft_split(path_envp, ":");
	i = -1;
	while (all_paths[++i])
	{
		path = ft_strjoin(ft_strjoin(ft_strdup(all_paths[i]), "/"), cmd[0]);
		if (access(path, X_OK) == 0)
			g_exitcode = execve(path, cmd, envp);
		free(path);
	}
	ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
	ft_free(all_paths);
	free(path_envp);
	exit(127);
}


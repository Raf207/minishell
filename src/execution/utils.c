/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:19:17 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/15 20:27:03 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_heredoc_input(int pipe[2], char *limiter)
{
	char	*line;

	close(pipe[0]);
	while (1)
	{
		ft_putstr_fd("", 0);
		line = get_next_line(0);
		if (!line)
			exit(EXIT_FAILURE);
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& (line[ft_strlen(limiter)] == '\n'))
		{
			close(pipe[1]);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, pipe[1]);
		free(line);
	}
}

int	ft_findpath(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH", envp[i], 4) == 0)
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
	path_envp = ft_substr(envp[ft_findpath(envp)], 5, 4654654);
	all_paths = ft_split(path_envp, ":");
	i = -1;
	while (all_paths[++i])
	{
		path = ft_strjoin(ft_strjoin(all_paths[i], "/"), cmd[0]);
		if (access(path, X_OK) == 0)
			execve(path, cmd, envp);
		free(path);
	}
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	ft_free(cmd);
	ft_free(all_paths);
	free(path_envp);
	exit(EXIT_FAILURE);
}

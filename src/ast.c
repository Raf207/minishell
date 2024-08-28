/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:28:09 by rafnasci          #+#    #+#             */
/*   Updated: 2024/08/28 04:33:09 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	parseredirection(t_token_list	*tokens)
void	free_split(char **split, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
		free(split[i]);
	free(split);
}

static void	ft_free(char **tabl)
{
	int	i;

	i = -1;
	while (tabl[++i])
		free(tabl[i]);
	free(tabl);
}

static int	ft_findpath(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (i);
	return (-1);
}

char	**split_cmd(t_token_list *tokens)
{
	int				args;
	int				i;
	t_token_list	*current;
	char			**split;

	args = 1;
	current = tokens->next;
	while (current->type == WORD)
	{
		args++;
		current = current->next;	
	}
	split = malloc(sizeof(char *) * (args + 1));
	if (!split)
		return (NULL);
	split[args] = 0;
	i = -1;
	while (++i < args)
	{
		split[i] = ft_strdup(tokens->value);
		if (!split[i])
			return (free_split(split, i), NULL);
		tokens = tokens->next;
	}
	return (split);
}

void	exec_cmd(t_token_list *tokens, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;
	char	*path_envp;
	char	**all_paths;

	cmd = split_cmd(tokens);
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

static t_AST	*createnode(char *type, t_token_list **value)
{
	t_AST			*node;
	t_token_list	*test;

	node = malloc(sizeof(t_AST));
	if (!node)
		return (NULL);
	node->left_child = NULL;
	node->right_child = NULL;
	node->type = ft_strdup(type);
	test = *value;
	node->value = *value;
	return (node);
}

t_AST	*parsecmd(t_token_list *tokens, t_env *env)
{
	t_AST	*top;

	if (tokens->type == WORD)
	{
		top = createnode("CMD", &tokens);
		while (tokens->type == WORD)
			tokens = tokens->next;
	}
	exec_cmd(top->value, build_env(&env));
	return (top);
}

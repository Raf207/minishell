/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:41:32 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/23 17:37:35 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_panic(char *s)
{
	ft_putendl_fd(s, 2);
	exit (1);
}

void	ft_exit_tokens(t_token_list **tokens, char *s)
{
	ft_putendl_fd(s, 2);
	ft_cleantoken(tokens);
	exit(1);
}

void	ft_free_ast(t_AST *node)
{
    if (node == NULL)
        return;
    if (node->type == EXEC)
    {
        if (node->argv)
            ft_free(node->argv);
		free(node);
    }
    else if (node->type == REDIR)
    {
        ft_free_ast(node->subcmd);
		free(node);
    }
	else if (node->type == N_HEREDOC)
    {
        ft_free_ast(node->subcmd);
		free(node);
    }
    else if (node->type == N_PIPE)
    {
        ft_free_ast(node->left);
        ft_free_ast(node->right);
		free(node);
    }
}

void	ft_free_env(t_env **list)
{
	t_env	*temp;
	t_env	*current;

	if (!list || !(*list))
		return ;
	current = *list;
	while (current)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		if (current->name)
			free(current->name);
		free(current);
		current = temp;
	}
	*list = NULL;
}

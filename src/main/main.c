/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/16 21:40:05 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

char	*ft_input(void)
{
	char	*input;

	input = readline("minishell >");
	if (input && *input)
		add_history(input);
	return (input);
}

void ft_display_ast(t_AST *node, int level)
{
    if (node == NULL)
        return;

    // Print indentation based on the level of the node in the tree
    for (int i = 0; i < level; i++)
        printf("  ");

    // Check the type of the node and print relevant information
    if (node->type == EXEC)
    {
        printf("Command: ");
        if (node->argv)
        {
            for (int i = 0; node->argv[i]; i++)
                printf("%s ", node->argv[i]);
            printf("\n");
        }
        else
        {
            printf("(no arguments)\n");
        }
    }
    else if (node->type == REDIR)
    {
        printf("Redirection: ");
        if (node->mode == 0 & O_RDONLY == 0)
            printf("Input redirection from file: %s\n", node->file);
        else if (node->mode & O_WRONLY)
        {
            if (node->mode & O_TRUNC)
                printf("Output redirection (truncate) to file: %s\n", node->file);
            else
                printf("Output redirection (append) to file: %s\n", node->file);
        }
        ft_display_ast(node->subcmd, level + 1);
    }
	else if (node->type == N_HEREDOC)
    {
        printf("Redirection: ");
        printf("here_doc redirection with limiter: %s\n", node->file);
        ft_display_ast(node->subcmd, level + 1);
    }
    else if (node->type == N_PIPE)
    {
        printf("Pipe:\n");
        ft_display_ast(node->left, level + 1); // Left side of the pipe
        ft_display_ast(node->right, level + 1); // Right side of the pipe
    }
}

void	ft_read_input(t_env **env)
{
	char			*input;
	t_token_list	*tokens;
	t_AST			*ast;
	char			**envp;
	int				copy_in;
	int				copy_out;

	copy_in = dup(0);
	copy_out = dup(1);
	signal(SIGINT, ft_sig_handler);
	while (1)
	{
		input = ft_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		tokens = ft_create_list(input);
		ast = ft_parsing(tokens);
		printf("-----------------------\nAST :\n");
		ft_display_ast(ast, 0);
		printf("-------------------------------\n");
		envp = build_env(env);
		if (ft_fork1() == 0)
			ft_runcmd(ast, envp, copy_in, copy_out);
		wait(0);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void) av;
	(void) ac;
	env = make_envlist(envp);
	ft_read_input(&env);
	return (0);
}
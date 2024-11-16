/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:16 by rafnasci          #+#    #+#             */
/*   Updated: 2024/11/16 19:01:40 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exitcode;

char	*ft_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input && *input)
		add_history(input);
	if (!input)
		printf("exit\n");
	return (input);
}

// void ft_display_ast(t_AST *node, int level)
// {
//     if (node == NULL)
//         return;

//     // Print indentation based on the level of the node in the tree
//     for (int i = 0; i < level; i++)
//         printf("  ");

//     // Check the type of the node and print relevant information
//     if (node->type == EXEC)
//     {
//         printf("Command: ");
//         if (node->argv)
//         {
//             for (int i = 0; node->argv[i]; i++)
//                 printf("%s ", node->argv[i]);
//             printf("\n");
//         }
//         else
//         {
//             printf("(no arguments)\n");
//         }
//     }
//     else if (node->type == REDIR)
//     {
//         printf("Redirection: ");
//         if (node->mode == 0 && O_RDONLY == 0)
//             printf("Input redirection from file: %s\n", node->file);
//         else if (node->mode && O_WRONLY)
//         {
//             if (node->mode == O_TRUNC)
//                 printf("Output redirection (truncate) to file: %s\n", node->file);
//             else
//                 printf("Output redirection (append) to file: %s\n", node->file);
//         }
//         ft_display_ast(node->subcmd, level + 1);
//     }
// 	else if (node->type == N_HEREDOC)
//     {
//         printf("Redirection: ");
//         printf("here_doc redirection with limiter: %s\n", node->file);
//         ft_display_ast(node->subcmd, level + 1);
//     }
//     else if (node->type == N_PIPE)
//     {
//         printf("Pipe:\n");
//         ft_display_ast(node->left, level + 1); // Left side of the pipe
//         ft_display_ast(node->right, level + 1); // Right side of the pipe
//     }
// }

void	ft_read_input(t_env **env)
{
	char			*input;
	t_AST			*ast;
	t_token_list	*tokens;
	char			**envp;
	int				copy_in;
	int				copy_out;

	tokens = NULL;
	copy_in = dup(0);
	copy_out = dup(1);
	while (1)
	{
		
		signal(SIGINT, ft_main_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		envp = build_env(env);
		if (!envp)
			continue ;
		input = ft_input();
		if (!input)
			break ;
		if (ft_create_list(input, env, &tokens))
		{
			ft_free(envp);
			free(input);
			continue ;
		}
		ast = ft_parsing(&tokens);
		ft_cleantoken(&tokens);
		dup2(copy_in, STDIN_FILENO);
		signal(SIGINT, ft_exec_sig_handler);
		signal(SIGQUIT, ft_exec_sig_handler);
		if (ast && input[0] != 0 && ast->type != N_PIPE
			&& ft_isbuiltin(ft_findexec(ast)))
			ft_runcmd(ast, envp, env);
		else if (ast && input[0] != 0 && ft_fork1() == 0)
		{
			ft_runcmd(ast, envp, env);
			ft_free_ast(ast);
			exit(0);
		}
		dup2(copy_out, STDOUT_FILENO);
		wait(0);
		ft_free(envp);
		unlink(".heredoc");
		free(input);
		ft_free_ast(ast);
		//system("leaks minishell");
	}
	ft_free_env(env);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void) av;
	(void) ac;
	env = make_envlist(envp);
	if (!env)
	{
		ft_putendl_fd("malloc error", 2);
		return (1);
	}
	ft_read_input(&env);
	return (0);
}

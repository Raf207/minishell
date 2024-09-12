/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:26:18 by rafnasci          #+#    #+#             */
/*   Updated: 2024/09/10 19:22:54 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dst;
	s = (const char *)src;
	i = -1;
	if (size == 0)
		return (strlen(s));
	while (++i < size - 1 && s[i])
		d[i] = s[i];
	d[i] = '\0';
	return (strlen(s));
}

char	*ft_strdup(const char *s)
{
	char	*dst;

	dst = (char *) malloc((strlen(s) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, strlen(s) + 1);
	return (dst);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*monstre;
// 	char	*txt[] = {"cat", "red", "blue", "green",0};

// 	// monstre = ft_strdup("< infile grep 1 | (cat -e | cat -e) > outfile;");
// 	// txt = strtok("< infile grep 1 | (cat -e | cat -e) > outfile;", ";");
// 	// while (txt != NULL)
// 	// {
// 	// 	printf("%s\n", txt);
// 	// 	txt = strtok(NULL, ";");
// 	// }
// 	execve("/bin/cat", txt, envp);
// 	printf("saluit\n");
// 	return (0);
// }

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)s;
	i = -1;
	while (++i < n)
		src[i] = c;
	return (s);
}

char	**ft_addargv(char **argv, char *arg)
{
	int		nb_args;
	char	**rep;

	if (!argv)
	{
		argv = malloc (sizeof(char *) * 2);
		if (!argv)
			return (NULL);
		argv[0] = ft_strdup(arg);
		if (!argv[0])
			return (free(argv), NULL);
		argv[1] = 0;
		return (argv);
	}
	nb_args = -1;
	while (argv[++nb_args])
		;
	rep = malloc(sizeof(char *) * (nb_args + 2));
	if (!rep)
		return (NULL);
	rep[nb_args + 1] = 0;
	rep[nb_args] = ft_strdup(arg);
	if (!rep)
		return (free(rep),NULL);
	while (--nb_args >= 0)
		rep[nb_args] = argv[nb_args];
	free(argv);
	return (rep);
}

int	main(void)
{
	t_AST	*ast;

	(void) ast;
	printf("mode : %d\n", O_WRONLY | O_TRUNC | O_CREAT);
	// ast = malloc(sizeof(*ast));
	// ft_memset(ast, 0, sizeof(*ast));
	// ast->argv = ft_addargv(ast->argv, "salut");
	// ast->argv = ft_addargv(ast->argv, "cava");
	// ast->argv = ft_addargv(ast->argv, "je suis une bete");
	// printf("mot : %s\n", ast->argv[0]);
	// printf("mot : %s\n", ast->argv[1]);
	// printf("mot : %s\n", ast->argv[2]);
	// free(ast->argv[0]);
	// free(ast->argv[1]);
	// free(ast->argv[2]);
	// free(ast->argv);
	// system("leaks a.out");
}

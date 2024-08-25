#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
# include <unistd.h>

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

int	main(int ac, char **av, char **envp)
{
	char	*monstre;
	char	*txt[] = {"cat", "red", "blue", "green",0};

	// monstre = ft_strdup("< infile grep 1 | (cat -e | cat -e) > outfile;");
	// txt = strtok("< infile grep 1 | (cat -e | cat -e) > outfile;", ";");
	// while (txt != NULL)
	// {
	// 	printf("%s\n", txt);
	// 	txt = strtok(NULL, ";");
	// }
	execve("/bin/cat", txt, envp);
	printf("saluit\n");
	return (0);
}

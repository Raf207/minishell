/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:00:06 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/30 17:33:51 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	swap_list(t_env *a, t_env *b)
{
	char	*tmp_name;
	char	*tmp_value;
	int		tmp_equal;

	tmp_name = a->name;
	tmp_value = a->value;
	tmp_equal = a->equal;
	a->name = b->name;
	a->value = b->value;
	a->equal = b->equal;
	b->name = tmp_name;
	b->value = tmp_value;
	b->equal = tmp_equal;
}

static void	sort_list(t_env *top)
{
	int		i;
	int		len;
	t_env	*list;

	if (!top)
		return ;
	i = 0;
	len = listlen(top);
	while (i < len)
	{
		list = top;
		while (list->next)
		{
			if (ft_strncmp(list->name, list->next->name,
					INT_MAX) > 0)
				swap_list(list, list->next);
			list = list->next;
		}
		i++;
	}
}

static t_env	*copy_list(t_env *top)
{
	t_env	*new_top;
	t_env	*prev;
	t_env	*new_node;

	new_top = NULL;
	prev = NULL;
	new_node = NULL;
	while (top)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->name = ft_strdup(top->name);
		new_node->value = ft_strdup(top->value);
		new_node->equal = top->equal;
		new_node->next = NULL;
		if (prev)
			prev->next = new_node;
		else
			new_top = new_node;
		prev = new_node;
		top = top->next;
	}
	return (new_top);
}

static void	print_list(t_env *top)
{
	while (top)
	{
		if (!top->value && !top->equal)
			ft_printf_fd(1, "declare -x %s\n", top->name);
		else if (!top->value && top->equal)
			ft_printf_fd(1, "declare -x %s=\"\"\n", top->name);
		else if (ft_strncmp(top->name, "_", INT_MAX))
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", top->name, top->value);
		top = top->next;
	}
}

void	sort_env(t_env *top)
{
	t_env	*list;

	list = copy_list(top);
	sort_list(list);
	print_list(list);
	free_list(list);
}

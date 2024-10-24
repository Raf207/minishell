/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:00:06 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/24 18:44:18 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	swap_env_node(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

static void	sort_list(t_env *top)
{
	int		swapped;
	t_env	*traveling_node;

	if (!top)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		traveling_node = top;
		while (traveling_node->next)
		{
			if (ft_strncmp(traveling_node->name, traveling_node->next->name,
					INT_MAX) > 0)
			{
				swap_env_node(traveling_node, traveling_node->next);
				swapped = 1;
			}
			traveling_node = traveling_node->next;
		}
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
	if (!top)
		ft_printf_fd(2, "no empty top \n");
	while (top)
	{
		if (!top->value)
			ft_printf_fd(1, "declare -x %s\n", top->name);
		else if (ft_strncmp(top->name, "_", INT_MAX))
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", top->name, top->value);
		top = top->next;
	}
	ft_printf_fd(1, "declare -x _=/usr/bin/env\n");
}

void	sort_env(t_env *top)
{
	t_env	*list;

	list = copy_list(top);
	sort_list(list);
	print_list(list);
	//	free_env_list(list);
}

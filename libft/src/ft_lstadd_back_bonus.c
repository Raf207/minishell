/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:24:52 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/18 13:09:21 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast((*lst));
		last->next = new;
	}
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*next;
// 	t_list	*back;
// 	t_list	*test;

// 	back = ft_lstnew("FIN ?");
// 	test = ft_lstnew("yuuuu ?");
// 	lst = ft_lstnew("yo");
// 	next = ft_lstnew(" Comment ca va ?");
// 	ft_lstadd_front(&lst, next);
// 	ft_lstadd_back(&lst, test);
// 	ft_lstadd_back(&lst, back);
// 	while (lst->next)
// 	{
// 		printf("content :%s\n", (char *) lst->content);
// 		lst = lst->next;
// 	}
// 	printf("content :%s\n", (char *) lst->content);
// }
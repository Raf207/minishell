/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:37 by rafnasci          #+#    #+#             */
/*   Updated: 2023/10/18 14:14:29 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!del || !lst || !(*lst))
		return ;
	temp = (*lst)->next;
	ft_lstdelone((*lst), del);
	while (temp != NULL)
	{
		*lst = temp;
		temp = temp->next;
		ft_lstdelone((*lst), del);
	}
	*lst = temp;
}

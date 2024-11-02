/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:34:54 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/01 21:34:58 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset(t_token_list *token, t_env **env)
{
    if (!env || !token->next->value)
        return ;
    printf("token : %s\n", token->value);
}

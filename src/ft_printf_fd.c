/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucabrin <mucabrin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:05:50 by mucabrin          #+#    #+#             */
/*   Updated: 2024/10/29 18:05:51 by mucabrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				ft_putstr_fd(va_arg(args, char *), fd);
			else if (format[i] == 'd')
				ft_putnbr_fd(va_arg(args, int), fd);
		}
		else
			ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (1);
}
//modif
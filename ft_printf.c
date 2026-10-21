/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:12 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/04 15:22:41 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printarg(va_list *args, char format)
{
	if (format == 'd' || format == 'i')
		return (ft_printnbr(va_arg(*args, int)));
	if (format == 's')
		return (ft_printstr(va_arg(*args, char *)));
	if (format == 'c')
		return (ft_printchar(va_arg(*args, int)));
	if (format == 'x')
		return (ft_printhex(va_arg(*args, unsigned int)));
	if (format == 'X')
		return (ft_printhexcap(va_arg(*args, unsigned int)));
	if (format == '%')
		return (ft_printchar('%'));
	if (format == 'u')
		return (ft_printunbr(va_arg(*args, unsigned int)));
	if (format == 'p')
		return (ft_printptr((unsigned long)va_arg(*args, void *)));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		size;
	int		printed;

	if (!str)
		return (-1);
	size = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
			printed = ft_printarg(&args, *++str);
		else
			printed = ft_printchar(*str);
		if (printed < 0 || size > INT_MAX - printed)
		{
			size = -1;
			break ;
		}
		size += printed;
		str++;
	}
	va_end(args);
	return (size);
}

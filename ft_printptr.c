/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:44 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/04 15:23:37 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(unsigned long n)
{
	int	size;

	if (!n)
		return (ft_printstr("(nil)"));
	if (ft_printstr("0x") < 0)
		return (-1);
	size = ft_printhex(n);
	if (size < 0)
		return (-1);
	return (size + 2);
}

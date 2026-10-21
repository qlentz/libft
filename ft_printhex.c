/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:19 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/04 15:23:01 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(unsigned long nb)
{
	int	size;
	int	last;

	size = 0;
	if (nb > 15)
		size = ft_printhex(nb / 16);
	if (size < 0)
		return (-1);
	last = nb % 16 + '0';
	if (nb % 16 > 9)
		last = nb % 16 - 10 + 'a';
	if (ft_printchar(last) < 0)
		return (-1);
	return (size + 1);
}

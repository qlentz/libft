/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexcap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:28 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/04 15:23:13 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexcap(unsigned long nb)
{
	int	size;
	int	last;

	size = 0;
	if (nb > 15)
		size = ft_printhexcap(nb / 16);
	if (size < 0)
		return (-1);
	last = nb % 16 + '0';
	if (nb % 16 > 9)
		last = nb % 16 - 10 + 'A';
	if (ft_printchar(last) < 0)
		return (-1);
	return (size + 1);
}

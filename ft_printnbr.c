/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:34 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/04 15:23:25 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n)
{
	unsigned int	nb;
	int				sign;
	int				size;

	nb = n;
	sign = 0;
	if (n < 0)
	{
		nb = 0U - nb;
		sign = ft_printchar('-');
		if (sign < 0)
			return (-1);
	}
	size = ft_printunbr(nb);
	if (size < 0)
		return (-1);
	return (size + sign);
}

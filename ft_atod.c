/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:23:38 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/07 13:25:03 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	d;
	double	d2;

	d = 0.0;
	d2 = 0.0;
	while (ft_isspace(*str))
		str++;
	while (*str && *str <= '9' && *str >= '0')
	{
		d *= 10;
		d += *str - '0';
		str++;
	}
	if (*str == '.')
		str++;
	while (*str && *str <= '9' && *str >= '0')
		str++;
	str--;
	while (*str && *str <= '9' && *str >= '0')
	{
		d2 += *str - '0';
		d2 /= 10;
		str--;
	}
	return (d + d2);
}

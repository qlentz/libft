/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:23:38 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/21 13:28:39 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	fractional_part(const char *str)
{
	double	value;
	double	place;

	value = 0.0;
	place = 0.1;
	while (ft_isdigit(*str))
	{
		value += (*str - '0') * place;
		place *= 0.1;
		str++;
	}
	return (value);
}

double	ft_atod(const char *str)
{
	double	value;
	int		sign;

	if (!str)
		return (0.0);
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	value = 0.0;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
		value += fractional_part(str + 1);
	return (sign * value);
}

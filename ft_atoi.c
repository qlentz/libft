/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:01:18 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/10 12:01:53 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	read_integer(const char *str, unsigned int limit)
{
	unsigned int	value;
	unsigned int	digit;

	value = 0;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (value > (limit - digit) / 10)
			return (limit);
		value = value * 10 + digit;
		str++;
	}
	return (value);
}

int	ft_atoi(const char *str)
{
	unsigned int	value;
	int				sign;

	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	value = read_integer(str, (unsigned int)INT_MAX + (sign < 0));
	if (sign < 0 && value > INT_MAX)
		return (INT_MIN);
	return ((int)value * sign);
}

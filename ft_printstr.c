/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:55 by qlentz            #+#    #+#             */
/*   Updated: 2022/11/04 15:23:48 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(const char *s)
{
	size_t	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (len > INT_MAX || write(1, s, len) != (ssize_t)len)
		return (-1);
	return ((int)len);
}

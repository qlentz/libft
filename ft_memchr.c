/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:03:46 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/10 12:03:48 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*bytes;
	size_t				i;

	bytes = str;
	i = 0;
	while (i < n)
	{
		if (bytes[i] == (unsigned char)c)
			return ((void *)(bytes + i));
		i++;
	}
	return (NULL);
}

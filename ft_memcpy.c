/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:04:16 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/10 17:02:08 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*out;
	const unsigned char	*in;
	size_t				i;

	out = dest;
	in = src;
	i = 0;
	while (i < n)
	{
		out[i] = in[i];
		i++;
	}
	return (dest);
}

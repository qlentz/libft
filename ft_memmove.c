/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:04:24 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/10 16:21:16 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*out;
	const unsigned char	*in;

	out = dest;
	in = src;
	if ((uintptr_t)out > (uintptr_t)in)
	{
		while (n > 0)
		{
			n--;
			out[n] = in[n];
		}
	}
	else if (dest != src)
		ft_memcpy(dest, src, n);
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:04:34 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/10 12:04:35 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = str;
	i = 0;
	while (i < n)
	{
		bytes[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

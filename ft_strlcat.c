/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:06:28 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/10 12:06:29 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	src_len;

	len = 0;
	src_len = ft_strlen(src);
	while (len < size && dest[len])
		len++;
	if (len == size)
		return (size + src_len);
	i = 0;
	while (i < size - len - 1 && src[i])
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (len + src_len);
}

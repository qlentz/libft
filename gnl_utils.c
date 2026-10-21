/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:38:48 by qlentz            #+#    #+#             */
/*   Updated: 2022/12/01 19:09:50 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_data(char **str)
{
	if (!str)
		return ;
	free(*str);
	*str = NULL;
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;

	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	if (!s1)
		return (ft_strdup(s2));
	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

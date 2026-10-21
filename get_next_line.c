/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:00:28 by qlentz            #+#    #+#             */
/*   Updated: 2022/12/01 19:10:15 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_chunks(int fd, char *rest, char *buf)
{
	ssize_t	count;

	count = 1;
	while (!ft_strchr(rest, '\n') && count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
		{
			free_data(&rest);
			return (NULL);
		}
		buf[count] = '\0';
		if (count > 0)
		{
			rest = ft_strjoin_gnl(rest, buf);
			if (!rest)
				return (NULL);
		}
	}
	return (rest);
}

static char	*clear_line(char **rest, char *line)
{
	free(line);
	free_data(rest);
	return (NULL);
}

static char	*extract_line(char **rest)
{
	char	*newline;
	char	*line;
	char	*next;

	newline = ft_strchr(*rest, '\n');
	if (!newline)
	{
		line = *rest;
		*rest = NULL;
		return (line);
	}
	line = ft_substr(*rest, 0, newline - *rest + 1);
	if (!line)
		return (clear_line(rest, NULL));
	next = ft_strdup(newline + 1);
	if (!next)
		return (clear_line(rest, line));
	free(*rest);
	*rest = next;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest[GNL_MAX_FD];
	char		*buf;

	if (fd < 0 || fd >= GNL_MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
		return (clear_line(&rest[fd], NULL));
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (clear_line(&rest[fd], NULL));
	rest[fd] = read_chunks(fd, rest[fd], buf);
	free(buf);
	if (!rest[fd] || !rest[fd][0])
		return (clear_line(&rest[fd], NULL));
	return (extract_line(&rest[fd]));
}

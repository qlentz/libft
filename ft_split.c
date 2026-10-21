/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:05:34 by qlentz            #+#    #+#             */
/*   Updated: 2022/10/12 11:26:45 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*new_word(const char *s, size_t len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

static char	**fill_words(char **words, const char *s, char c)
{
	size_t	count;
	size_t	len;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		words[count] = new_word(s, len);
		if (!words[count])
		{
			ft_free_tab(words);
			return (NULL);
		}
		count++;
		s += len;
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	return (fill_words(words, s, c));
}

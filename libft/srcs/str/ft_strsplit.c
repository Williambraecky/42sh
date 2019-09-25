/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:00:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/18 10:38:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_split_count_words(const char *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		words += *s != '\0';
		while (*s && *s != c)
			s++;
	}
	return (words);
}

static size_t	ft_split_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**split;
	size_t	words;
	size_t	current_wordlen;
	size_t	i;

	if (s == NULL)
		return (NULL);
	words = ft_split_count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		current_wordlen = ft_split_len(s, c);
		if ((split[i] = ft_strnew(current_wordlen)) == NULL)
			return (NULL);
		ft_strncpy(split[i], s, current_wordlen);
		s += current_wordlen;
		i++;
	}
	split[i] = NULL;
	return (split);
}

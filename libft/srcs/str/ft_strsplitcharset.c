/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitcharset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:54:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/04 15:59:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_in_str(char *set, char c)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

static size_t	count_words(const char *str, char *set)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		while (is_in_str(set, *str))
			str++;
		words += *str != '\0';
		while (*str && !is_in_str(set, *str))
			str++;
	}
	return (words);
}

static size_t	split_len(const char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_in_str(set, *str))
		i++;
	return (i);
}

char			**ft_strsplitcharset(const char *str, char *set)
{
	char	**split;
	size_t	words;
	size_t	current_wordlen;
	size_t	i;

	if (str == NULL)
		return (NULL);
	words = count_words(str, set);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (is_in_str(set, *str))
			str++;
		current_wordlen = split_len(str, set);
		if ((split[i] = ft_strnew(current_wordlen)) == NULL)
			return (NULL);
		ft_strncpy(split[i], str, current_wordlen);
		str += current_wordlen;
		i++;
	}
	split[i] = NULL;
	return (split);
}

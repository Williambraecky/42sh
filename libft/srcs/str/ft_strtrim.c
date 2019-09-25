/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 12:25:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/18 10:38:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isspace(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}

static size_t	ft_last_char(const char *s)
{
	size_t	i;

	i = ft_strlen(s);
	while (i-- && ft_isspace(s[i]))
		;
	return (i);
}

static size_t	ft_first_char(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}

char			*ft_strtrim(const char *s)
{
	size_t	first_char;
	size_t	last_char;
	int		s_len;

	if (s == NULL)
		return (NULL);
	first_char = ft_first_char(s);
	last_char = ft_last_char(s);
	s_len = (int)last_char - (int)first_char + 1;
	if (s_len < 0)
		s_len = 0;
	return (ft_strsub(s, first_char, (size_t)s_len));
}

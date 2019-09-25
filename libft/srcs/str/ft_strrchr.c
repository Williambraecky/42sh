/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:23:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 23:17:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	to_find;

	to_find = (char)c;
	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + i);
	while (i--)
	{
		if (s[i] == to_find)
			return ((char *)(s + i));
	}
	return (NULL);
}

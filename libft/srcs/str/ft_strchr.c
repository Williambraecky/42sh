/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:18:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 23:16:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	to_find;

	to_find = (char)c;
	while (*s)
	{
		if (*s++ == to_find)
			return ((char *)--s);
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:32:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 23:18:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	while (*haystack && len--)
	{
		j = 0;
		while (haystack[j] == needle[j] && j <= len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack);
			j++;
		}
		haystack++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:26:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 10:21:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	while (*haystack)
	{
		j = 0;
		while (haystack[j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack);
			j++;
		}
		haystack++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 11:49:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/18 10:40:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*map;

	if (s == NULL || f == NULL)
		return (NULL);
	map = ft_strnew(ft_strlen(s));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		map[i] = f(i, *s++);
		i++;
	}
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 12:19:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 22:41:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	char	*join;

	i = 0;
	if (s1)
		i += ft_strlen(s1);
	if (s2)
		i += ft_strlen(s2);
	join = ft_strnew(i);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		join[i++] = *s1++;
	while (s2 && *s2)
		join[i++] = *s2++;
	return (join);
}

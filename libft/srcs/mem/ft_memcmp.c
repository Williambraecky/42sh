/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 11:03:32 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 17:03:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	if (s1 == s2)
		return (0);
	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*c_s1++ != *c_s2++)
			return ((int)(*--c_s1 - *--c_s2));
	}
	return (0);
}

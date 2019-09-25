/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:09:48 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 23:13:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;
	unsigned char	find;

	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	find = (unsigned char)c;
	while (n--)
	{
		*c_dst = *c_src;
		if (*c_dst == find)
			return ((void *)(c_dst + 1));
		c_dst++;
		c_src++;
	}
	return (NULL);
}

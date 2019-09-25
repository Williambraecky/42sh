/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:53:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 09:49:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	find;

	p = (unsigned char *)s;
	find = (unsigned char)c;
	while (n--)
	{
		if (*p++ == find)
			return ((void *)(--p));
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:57:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/16 09:41:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*c_dst;
	unsigned char	u_c;

	c_dst = (unsigned char *)b;
	u_c = (unsigned char)c;
	while (len--)
		*c_dst++ = u_c;
	return (b);
}

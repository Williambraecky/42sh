/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:30:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/16 19:49:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wstrindex(char *str, size_t index)
{
	size_t	len;

	len = 0;
	if (index == 0)
		return (str);
	while (*str)
	{
		if (len == index)
			return (str);
		if ((*str & 0xC0) != 0x80)
			len++;
		str++;
	}
	return (str);
}

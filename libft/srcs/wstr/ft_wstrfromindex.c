/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrfromindex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:41:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:50:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrfromindex(char *str, size_t index)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (*str)
	{
		if ((*str & 0xC0) != 0x80)
			len++;
		if (i == index)
			return (len - 1);
		str++;
		i++;
	}
	return (len);
}

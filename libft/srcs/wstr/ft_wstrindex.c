/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:30:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/11 16:31:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wstrindex(char *str, size_t index)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if ((*str & 0xC0) != 0x80)
			len++;
		if (len == index)
			return (str);
		str++;
	}
	return (NULL);
}

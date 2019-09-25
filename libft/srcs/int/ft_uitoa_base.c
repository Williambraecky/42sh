/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 13:54:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/13 13:57:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(size_t value, size_t basesize)
{
	char	*str;
	size_t	len;

	len = ft_uintlen_base(value, basesize);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		str[len] = ft_itoc_base(value % basesize, basesize);
		value /= basesize;
	}
	return (str);
}

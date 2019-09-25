/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:26:53 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/13 13:40:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(ssize_t value, size_t basesize)
{
	char	*result;
	size_t	negative;
	size_t	nblen;

	negative = value < 0 && basesize == 10;
	nblen = ft_intlen_base(value, basesize) + negative;
	result = ft_strnew(nblen);
	if (result == NULL)
		return (NULL);
	if (negative)
		result[0] = '-';
	while (nblen-- > negative)
	{
		result[nblen] = ft_itoc_base(value, basesize);
		value /= (int)basesize;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:40:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/25 14:40:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_should_skip(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' ||
			c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long			ft_atol(const char *str)
{
	unsigned long	nbr;
	unsigned long	limit;
	int				negative;

	while (ft_should_skip(*str))
		str++;
	negative = *str == '-' ? -1 : 1;
	str += *str == '+' || *str == '-';
	nbr = 0;
	limit = negative == -1 ? 9223372036854775808UL :
		(unsigned long)LIB_LONG_MAX;
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10 + ((unsigned long)(*str++ - '0'));
		if (nbr > limit)
			return ((long)limit);
	}
	return ((long)nbr * negative);
}

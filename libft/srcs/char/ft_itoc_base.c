/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoc_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 09:10:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/13 13:58:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_itoc_base(ssize_t value, size_t basesize)
{
	value %= (ssize_t)basesize;
	if (value < 0)
		value = -value;
	if (value < 10)
		return (value + '0');
	else
		return (value - 10 + 'A');
}

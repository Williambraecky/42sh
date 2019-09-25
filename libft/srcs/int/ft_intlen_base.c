/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 09:20:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/13 13:45:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen_base(ssize_t value, size_t basesize)
{
	size_t i;

	if (value == 0)
		return (1);
	i = 0;
	while (value != 0)
	{
		value /= (ssize_t)basesize;
		i++;
	}
	return (i);
}

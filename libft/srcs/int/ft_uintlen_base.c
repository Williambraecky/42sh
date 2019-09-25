/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintlen_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 13:43:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/13 13:44:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_uintlen_base(size_t value, size_t basesize)
{
	size_t len;

	len = 1;
	while (value > (basesize - 1) && len++)
		value /= basesize;
	return (len);
}

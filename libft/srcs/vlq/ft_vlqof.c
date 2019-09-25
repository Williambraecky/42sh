/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:48:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/18 17:52:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq	ft_vlqof(t_u64 value)
{
	t_vlq	result;
	size_t	len;

	len = value & (1l << 63) ? 2 : 1;
	if (!(result = ft_vlqnew(len)))
		return (NULL);
	result[0] |= (value & _NOMSB_);
	if (len == 2)
		result[1] |= 1;
	return (result);
}

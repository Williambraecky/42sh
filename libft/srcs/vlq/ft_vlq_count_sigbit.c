/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_count_sigbit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:31:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/18 17:51:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_u32	ft_vlq_count_sigbit_part(t_u64 part)
{
	t_u32	count;

	count = 0;
	part &= _NOMSB_;
	while (part)
	{
		count++;
		part >>= 1;
	}
	return (count);
}

t_u32	ft_vlq_count_sigbit(t_vlq vlq)
{
	size_t	len;

	len = ft_vlqlen(vlq);
	if (len == 1 && (*vlq & _NOMSB_) == 0)
		return (0);
	return ((len - 1) * 63 + ft_vlq_count_sigbit_part(vlq[len - 1]));
}

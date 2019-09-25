/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_count_actbits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:53:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/18 17:55:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_u32	ft_vlq_count_actbits(t_vlq vlq)
{
	t_u32	count;
	t_u64	current;
	size_t	len;
	size_t	i;

	len = ft_vlqlen(vlq);
	count = 0;
	while (len--)
	{
		current = vlq[len];
		i = 63;
		while (i--)
			if (current & (1l << i))
				count++;
	}
	return (count);
}

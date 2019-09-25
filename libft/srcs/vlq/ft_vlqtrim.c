/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:15:54 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/18 17:52:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vlqtrim(t_vlq *vlq)
{
	t_vlq	result;
	size_t	len;

	len = ft_vlqlen(*vlq);
	if (len == 1)
		return ;
	while (len--)
		if (*vlq[len] & _NOMSB_)
			break ;
	if (len == ft_vlqlen(*vlq) - 1)
		return ;
	if (!(result = ft_vlqnew(len)))
		return ;
	while (len--)
		result[len] |= *vlq[len];
	ft_vlqdel(vlq);
	*vlq = result;
}

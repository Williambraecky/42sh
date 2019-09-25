/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:53:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/18 17:52:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq	ft_vlqnew(size_t len)
{
	t_vlq	vlq;

	if (len == 0 || !(vlq = ft_memalloc(sizeof(*vlq) * len)))
		return (NULL);
	len--;
	while (len--)
		vlq[len] |= (1l << 63);
	return (vlq);
}

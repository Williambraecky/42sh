/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:40:48 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/17 16:42:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq	ft_vlqdup(t_vlq vlq)
{
	t_vlq	dup;
	size_t	len;

	len = ft_vlqlen(vlq);
	if (len == 0 || !(dup = malloc(sizeof(*dup) * len)))
		return (NULL);
	while (len--)
		dup[len] = vlq[len];
	return (dup);
}

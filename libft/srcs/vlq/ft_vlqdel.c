/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:08:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/17 16:10:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vlqdel(t_vlq *vlq)
{
	if (!vlq || !*vlq)
		return ;
	ft_memset(*vlq, 0, ft_vlqlen(*vlq) * sizeof(**vlq));
	free(*vlq);
	*vlq = NULL;
}

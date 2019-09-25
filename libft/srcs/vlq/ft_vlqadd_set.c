/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqadd_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:31:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/17 17:32:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vlqadd_set(t_vlq *vlq, t_vlq b)
{
	t_vlq	result;

	result = ft_vldadd(*vlq, b);
	ft_vlqdel(vlq);
	*vlq = result;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_subst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:04:24 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 19:05:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_subst(t_subst *subst)
{
	ft_strdel(&subst->buffer.buffer);
	ft_vecfree(&subst->stack);
}

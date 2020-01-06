/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:37:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 00:24:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	free_prompt(t_prompt *prompt)
{
	ft_strdel(&prompt->prompt);
	if (prompt->select.poss.vec)
		ft_vecfree(&prompt->select.poss);
}

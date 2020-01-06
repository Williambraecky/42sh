/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 00:01:57 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 00:17:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: proper full render procedure for select
** NOTE: since rendering the line clears the rest of the screen, the line has to be changed first so `change_line` should be remade aswell
** NOTE: we should probably process informations such as elem_per_row etc here
** NOTE: this function should not disrupt the current cursor position
*/

int		select_render(t_prompt *prompt, t_select *select)
{
	t_vec	*poss;

	(void)prompt;
	poss = &select->poss;
	return (SH_SUCCESS);
}

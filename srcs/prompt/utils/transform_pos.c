/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:56:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 01:56:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void		transform_pos(t_prompt *prompt, t_pos *pos, char c)
{
	if (c == '\n')
		pos->x = prompt->winsize.ws_col;
	else if (c == '\t')
		pos->x += 8 - pos->x % 8;
	else
		pos->x++;
	if (pos->x >= prompt->winsize.ws_col)
	{
		pos->x = 0;
		pos->y++;
	}
}

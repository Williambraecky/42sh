/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_cursor_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:31:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/17 21:00:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** Because for some reason the cursor can go behind limits with write /shrug
*/

t_pos	calc_write_cursor_pos(t_prompt *prompt, size_t written)
{
	t_pos	pos;

	if (written == 0)
	{
		pos.x = 0;
		pos.y = 0;
		return (pos);
	}
	if ((written % prompt->winsize.ws_col) == 0)
	{
		pos.x = written % (prompt->winsize.ws_col + 1);
		pos.y = written / (prompt->winsize.ws_col + 1);
	}
	else
	{
		pos.x = written % prompt->winsize.ws_col;
		pos.y = written / prompt->winsize.ws_col;
	}
	return (pos);
}

/*
** Returns t_pos relative to starting point from number of written characters
** doesn't count when a newline or second prompt is present
*/

t_pos	calc_cursor_pos(t_prompt *prompt, size_t written)
{
	t_pos	pos;

	if (written == 0)
	{
		pos.x = 0;
		pos.y = 0;
		return (pos);
	}
	pos.x = written % prompt->winsize.ws_col;
	pos.y = written / prompt->winsize.ws_col;
	return (pos);
}

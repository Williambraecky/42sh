/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/12 16:46:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	transform_pos(t_prompt *prompt, t_pos *pos, char c)
{
	if (c == '\n')
		pos->x = prompt->winsize.ws_col;
	else if (c == '\t')
		pos->x += 8 - pos->x % 8;
	else
		pos->x++;
	if (pos->x == prompt->winsize.ws_col)
	{
		pos->x = 0;
		pos->y++;
	}
}

int			default_char_handler(t_prompt *prompt, char *buffer)
{
	t_pos	new;

	if (buff_insert(&prompt->buffer, buffer, prompt->buffer_index)
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	new = prompt->cursor_pos;
	transform_pos(prompt, &new, *buffer);
	print_from_cursor(prompt, &new);
	prompt->buffer_index += wcharlen(*buffer);
	prompt->char_index++;
	return (RET_CONT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/08 17:24:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			default_char_handler(t_prompt *prompt, char *buffer)
{
	t_pos	new;

	if (buff_insert(&prompt->buffer, buffer, prompt->buffer_index)
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	new = prompt->cursor_pos;
	new.x++;
	if (new.x == prompt->winsize.ws_col)
	{
		new.x = 0;
		new.y++;
	}
	print_from_cursor(prompt, &new);
	prompt->buffer_index += wcharlen(*buffer);
	prompt->char_index++;
	return (RET_CONT);
}

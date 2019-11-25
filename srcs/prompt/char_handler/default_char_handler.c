/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/25 18:41:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	print(t_prompt *prompt)
{
	t_pos	new;

	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(prompt->buffer.buffer + prompt->buffer_index, 0);
	new = new_calc_write(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer.buffer));
	if (new.x == prompt->winsize.ws_col)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		new.x = 0;
		new.y++;
	}
	prompt->cursor_pos.x++;
	if (prompt->cursor_pos.x == prompt->winsize.ws_col)
	{
		prompt->cursor_pos.x = 0;
		prompt->cursor_pos.y++;
	}
	new.x = prompt->cursor_pos.x - new.x;
	new.y = prompt->cursor_pos.y - new.y;
	move_cursor(new);
}

int			default_char_handler(t_prompt *prompt, char *buffer)
{
	if (buff_insert(&prompt->buffer, buffer, prompt->buffer_index)
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	print(prompt);
	prompt->buffer_index += wcharlen(*buffer);
	prompt->char_index++;
	return (RET_CONT);
}

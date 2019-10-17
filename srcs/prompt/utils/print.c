/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:51:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/17 21:12:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	reprint_buffer(t_prompt *prompt)
{
	t_pos	new;
	t_pos	max;
	t_pos	max_back;

	new.x = prompt->prompt_pos.x - prompt->cursor_pos.x;
	new.y = prompt->prompt_pos.y - prompt->cursor_pos.y;
	move_cursor(new);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(prompt->buffer, 0);
	new = calc_write_cursor_pos(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer));
	max = calc_cursor_pos(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer));
	prompt->cursor_pos = calc_cursor_pos(prompt,
		prompt->prompt_len + prompt->char_index);
	max_back = max;
	max.x -= new.x;
	max.y -= new.y;
	move_cursor(max);
	max = max_back;
	new.x = prompt->cursor_pos.x - max.x;
	new.y = prompt->cursor_pos.y - max.y;
	move_cursor(new);
}

/*
** TODO: move cursor back to prompt print all then move cursor back
*/

void	print_buffer(t_prompt *prompt)
{
	t_pos	new;

	new = calc_cursor_pos(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer));
	if (new.x == 0)
	{
		new.y -= 1;
		new.x = prompt->winsize.ws_col;
	}
	new.x = prompt->cursor_pos.x - new.x;
	new.y = prompt->cursor_pos.y - new.y;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(ft_wstrindex(prompt->buffer, prompt->char_index), 0);
	move_cursor(new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:42:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 02:00:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void		move_goto(t_prompt *prompt, t_pos pos)
{
	t_pos	rel;

	rel.y = pos.y - prompt->cursor_pos.y;
	if (rel.y > 0)
		rel.x = pos.x;
	else
		rel.x = pos.x - prompt->cursor_pos.x;
	move_cursor(rel);
	prompt->cursor_pos = pos;
}

void		move_cursor(t_pos rel_pos)
{
	if (rel_pos.y > 0)
		while (rel_pos.y--)
			ft_putstr_fd(tgetstr("do", NULL), 0);
	else if (rel_pos.y < 0)
		while (rel_pos.y++)
			ft_putstr_fd(tgetstr("up", NULL), 0);
	if (rel_pos.x > 0)
		while (rel_pos.x--)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
	else if (rel_pos.x < 0)
		while (rel_pos.x++)
			ft_putstr_fd(tgetstr("le", NULL), 0);
}

void		move_left(t_prompt *prompt)
{
	t_pos	pos;
	t_pos	back;

	if (prompt->char_index == 0)
		return ;
	pos = calc_cursor_pos(prompt, prompt->char_index - 1);
	prompt->char_index -= 1;
	prompt->buffer_index =
		ft_wstrindex(prompt->buffer.buffer, prompt->char_index)
		- prompt->buffer.buffer;
	back = pos;
	pos.x -= prompt->cursor_pos.x;
	pos.y -= prompt->cursor_pos.y;
	prompt->cursor_pos = back;
	move_cursor(pos);
}

void		move_right(t_prompt *prompt)
{
	t_pos new;

	if (!prompt->buffer.buffer[prompt->buffer_index])
		return ;
	new = prompt->cursor_pos;
	transform_pos(prompt, &new, prompt->buffer.buffer[prompt->buffer_index]);
	prompt->buffer_index +=
		wcharlen(prompt->buffer.buffer[prompt->buffer_index]);
	prompt->char_index++;
	move_goto(prompt, new);
}

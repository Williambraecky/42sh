/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:42:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 16:26:07 by wbraeckm         ###   ########.fr       */
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
			ft_putstr_fd(tgoto(tgetstr("do", NULL), 0, 0), 0);
	else if (rel_pos.y < 0)
		while (rel_pos.y++)
			ft_putstr_fd(tgoto(tgetstr("up", NULL), 0, 0), 0);
	if (rel_pos.x > 0)
		while (rel_pos.x--)
			ft_putstr_fd(tgoto(tgetstr("nd", NULL), 0, 0), 0);
	else if (rel_pos.x < 0)
		while (rel_pos.x++)
			ft_putstr_fd(tgoto(tgetstr("le", NULL), 0, 0), 0);
}

/*
** TODO: when on x == 0 go back to x = winsize.win_col and y - 1
*/

void		move_left(t_prompt *prompt, size_t amnt)
{
	t_pos	pos;
	t_pos	back;

	if (prompt->char_index == 0)
		return ;
	pos = new_calc(prompt,
		prompt->prompt_len + prompt->char_index - amnt);
	prompt->char_index -= amnt;
	prompt->buffer_index =
		ft_wstrindex(prompt->buffer, prompt->char_index) - prompt->buffer;
	back = pos;
	pos.x -= prompt->cursor_pos.x;
	pos.y -= prompt->cursor_pos.y;
	prompt->cursor_pos = back;
	move_cursor(pos);
}

/*
** TODO: when on x == winsize.win_col go back to x = 0 and y + 1
*/

void		move_right(t_prompt *prompt, size_t amnt)
{
	t_pos	pos;
	t_pos	back;

	if (prompt->char_index == ft_wstrlen(prompt->buffer))
		return ;
	pos = new_calc(prompt,
		prompt->prompt_len + prompt->char_index + amnt);
	prompt->char_index += amnt;
	prompt->buffer_index =
		ft_wstrindex(prompt->buffer, prompt->char_index) - prompt->buffer;
	back = pos;
	pos.y -= prompt->cursor_pos.y;
	if (pos.y == 0)
		pos.x -= prompt->cursor_pos.x;
	prompt->cursor_pos = back;
	move_cursor(pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:42:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/16 23:02:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	can_move(t_prompt *prompt, t_pos pos)
{
	t_pos	prompt_pos;
	t_pos	max_pos;

	prompt_pos = prompt->prompt_pos;
	if (prompt_pos.y < pos.y
		|| (prompt_pos.y == pos.y && prompt_pos.x > pos.x))
		return (0);
	max_pos = calc_cursor_pos(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer));
	if (pos.y < max_pos.y)
		return (1);
	else if (pos.y == max_pos.y && pos.x <= max_pos.x)
		return (1);
	return (0);
}

void		move_cursor(t_pos rel_pos)
{
	if (rel_pos.y > 0)
		ft_putstr_fd(tgoto(tgetstr("do", NULL), 0, rel_pos.y), 0);
	else if (rel_pos.y < 0)
		ft_putstr_fd(tgoto(tgetstr("up", NULL), 0, -rel_pos.y), 0);
	if (rel_pos.x > 0)
		ft_putstr_fd(tgoto(tgetstr("nd", NULL), rel_pos.x, 0), 0);
	else if (rel_pos.x < 0)
		ft_putstr_fd(tgoto(tgetstr("le", NULL), -rel_pos.x, 0), 0);
}

void		move_left(t_prompt *prompt, size_t amnt)
{
	t_pos	pos;
	t_pos	back;

	pos = calc_cursor_pos(prompt,
		prompt->prompt_len + prompt->char_index - amnt);
	if (!can_move(prompt, pos))
		return ;
	prompt->char_index -= amnt;
	prompt->buffer_index =
		ft_wstrindex(prompt->buffer, prompt->char_index) - prompt->buffer;
	back = pos;
	pos.x -= prompt->cursor_pos.x;
	pos.y -= prompt->cursor_pos.y;
	prompt->cursor_pos = back;
	move_cursor(pos);
}

void		move_right(t_prompt *prompt, size_t amnt)
{
	t_pos	pos;
	t_pos	back;

	pos = calc_cursor_pos(prompt,
		prompt->prompt_len + prompt->char_index + amnt);
	if (!can_move(prompt, pos))
		return ;
	prompt->char_index += amnt;
	prompt->buffer_index =
		ft_wstrindex(prompt->buffer, prompt->char_index) - prompt->buffer;
	back = pos;
	pos.x -= prompt->cursor_pos.x;
	pos.y -= prompt->cursor_pos.y;
	prompt->cursor_pos = back;
	move_cursor(pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:51:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/08 01:22:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int		check_edit_line(t_prompt *prompt,
	size_t i, size_t curr_line)
{
	if (i < prompt->edit_from && i + curr_line >= prompt->edit_from)
		return (1);
	else if (i >= prompt->edit_from && i < prompt->edit_to)
		return (1);
	return (0);
}

static size_t	calc_line_size(t_prompt *prompt, size_t index, t_pos *pos)
{
	size_t	len;
	t_pos	orig_pos;

	len = 0;
	orig_pos = *pos;
	while (prompt->buffer.buffer[index + len])
	{
		transform_pos(prompt, pos, prompt->buffer.buffer[index + len]);
		len += wcharlen(prompt->buffer.buffer[index + len]);
		if (pos->y != orig_pos.y)
			break ;
	}
	return (len);
}

/*
** NOTE: reprints everything from the cursor line by line,
** if next_pos is NULL moves back to prompt->cursor_pos
*/

static void		edit_mode_print(t_prompt *prompt,
	size_t index, size_t curr_line)
{
	if (index < prompt->edit_from)
	{
		write(0, prompt->buffer.buffer + index, prompt->edit_from - index);
		curr_line -= prompt->edit_from - index;
		index += prompt->edit_from - index;
	}
	ft_putstr_fd(tgetstr("so", NULL), 0);
	if (index + curr_line < prompt->edit_to)
	{
		write(0, prompt->buffer.buffer + index, curr_line);
		index += curr_line;
		curr_line = 0;
	}
	else
	{
		write(0, prompt->buffer.buffer + index, prompt->edit_to - index);
		curr_line -= prompt->edit_to - index;
		index += prompt->edit_to - index;
	}
	ft_putstr_fd(tgetstr("se", NULL), 0);
	if (curr_line)
		write(0, prompt->buffer.buffer + index, curr_line);
}

void			print_from_cursor(t_prompt *prompt, t_pos *next_pos)
{
	size_t	index;
	size_t	curr_line;
	t_pos	pos;

	if (next_pos == NULL)
		next_pos = &prompt->cursor_pos;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	index = prompt->buffer_index;
	pos = prompt->cursor_pos;
	while (prompt->buffer.buffer[index])
	{
		curr_line = calc_line_size(prompt, index, &pos);
		if (prompt->edit_mode && check_edit_line(prompt, index, curr_line))
			edit_mode_print(prompt, index, curr_line);
		else
			write(0, prompt->buffer.buffer + index, curr_line);
		index += curr_line;
		if (prompt->buffer.buffer[index - 1] != '\n' && pos.x == 0)
			ft_putstr_fd(tgetstr("do", NULL), 0);
	}
	prompt->max_pos = pos;
	pos.x = next_pos->x - pos.x;
	pos.y = next_pos->y - pos.y;
	move_cursor(pos);
	prompt->cursor_pos = *next_pos;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:51:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/12 17:21:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: currently unstable
*/

/*
** NOTE: reprints whole buffer
*/

void			reprint_buffer(t_prompt *prompt)
{
	t_pos	back;
	size_t	buffer_index_back;
	size_t	char_index_back;

	back = prompt->cursor_pos;
	buffer_index_back = prompt->buffer_index;
	char_index_back = prompt->char_index;
	prompt->buffer_index = 0;
	prompt->char_index = 0;
	move_goto(prompt, prompt->prompt_pos);
	print_from_cursor(prompt, &back);
	prompt->buffer_index = buffer_index_back;
	prompt->char_index = char_index_back;
}

static void		transform_pos(t_prompt *prompt, t_pos *pos, char c)
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

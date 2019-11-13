/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_cursor_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:31:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/07 15:12:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** Because for some reason the cursor can go behind limits with write /shrug
*/

static t_pos	new_calc_write_prompt(t_prompt *prompt, size_t written)
{
	t_pos	pos;
	size_t	p_index;
	size_t	i;

	i = 0;
	p_index = 0;
	pos.x = 0;
	pos.y = 0;
	while (i < written && i < prompt->prompt_len)
	{
		if (prompt->prompt[p_index] != '\n')
			pos.x++;
		if (pos.x == prompt->winsize.ws_col + 1
			|| prompt->prompt[p_index] == '\n')
		{
			pos.x = prompt->prompt[p_index] == '\n' ? 0 : 1;
			pos.y++;
		}
		p_index += wcharlen(prompt->prompt[p_index]);
		i++;
	}
	return (pos);
}

/*
** TODO: obsolete this by printing every line separately and forcing newline
*/

t_pos			new_calc_write(t_prompt *prompt, size_t written)
{
	t_pos	pos;
	size_t	p_index;
	size_t	i;

	pos = new_calc_write_prompt(prompt, written);
	if (prompt->prompt_len < written)
		written -= prompt->prompt_len;
	else
		written = 0;
	i = 0;
	p_index = 0;
	while (i < written && i <= ft_wstrlen(prompt->buffer))
	{
		if (prompt->buffer[p_index] != '\n')
			pos.x++;
		if (pos.x == prompt->winsize.ws_col + 1
			|| prompt->buffer[p_index] == '\n')
		{
			pos.x = prompt->buffer[p_index] == '\n' ? 0 : 1;
			pos.y++;
		}
		p_index += wcharlen(prompt->buffer[p_index]);
		i++;
	}
	return (pos);
}

static t_pos	new_calc_prompt(t_prompt *prompt, size_t written)
{
	t_pos	pos;
	size_t	p_index;
	size_t	i;

	i = 0;
	p_index = 0;
	pos.x = 0;
	pos.y = 0;
	while (i < written && i < prompt->prompt_len)
	{
		if (prompt->prompt[p_index] != '\n')
			pos.x++;
		if (pos.x == prompt->winsize.ws_col || prompt->prompt[p_index] == '\n')
		{
			pos.x = 0;
			pos.y++;
		}
		p_index += wcharlen(prompt->prompt[p_index]);
		i++;
	}
	return (pos);
}

t_pos			new_calc(t_prompt *prompt, size_t written)
{
	t_pos	pos;
	size_t	p_index;
	size_t	i;

	pos = new_calc_prompt(prompt, written);
	if (prompt->prompt_len < written)
		written -= prompt->prompt_len;
	else
		written = 0;
	i = 0;
	p_index = 0;
	while (i < written && i <= ft_wstrlen(prompt->buffer))
	{
		if (prompt->buffer[p_index] != '\n')
			pos.x++;
		if (pos.x == prompt->winsize.ws_col || prompt->buffer[p_index] == '\n')
		{
			pos.x = 0;
			pos.y++;
		}
		p_index += wcharlen(prompt->buffer[p_index]);
		i++;
	}
	return (pos);
}

/*
** NOTE: are there any other special cases?
*/

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

/*
** New method handles tabs and newlines better needs another function to
** calculate prompt position //assumes prompt->prompt_pos is always correct
** TODO: pos to written method
*/

t_pos			calc_prompt_pos(t_prompt *prompt)
{
	t_pos	pos;
	size_t	i;

	pos = (t_pos){.x = 0, .y = 0};
	i = 0;
	while (prompt->prompt[i])
	{
		transform_pos(prompt, &pos, prompt->prompt[i]);
		i += wcharlen(prompt->prompt[i]);
	}
	return (pos);
}

t_pos			calc_cursor_pos(t_prompt *prompt, size_t written)
{
	t_pos	pos;
	size_t	i;

	pos = prompt->prompt_pos;
	i = 0;
	while (written-- && prompt->buffer[i])
	{
		transform_pos(prompt, &pos, prompt->buffer[i]);
		i += wcharlen(prompt->buffer[i]);
	}
	return (pos);
}

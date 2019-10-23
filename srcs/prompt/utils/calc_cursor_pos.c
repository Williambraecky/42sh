/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_cursor_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:31:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 18:22:52 by wbraeckm         ###   ########.fr       */
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

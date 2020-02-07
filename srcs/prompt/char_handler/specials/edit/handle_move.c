/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:00:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 22:00:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static size_t	prev_index(t_prompt *prompt, size_t index)
{
	if (index == 0)
		return (0);
	return (ft_wstrindex(prompt->buffer.buffer,
		ft_wstrfromindex(prompt->buffer.buffer, index) - 1)
		- prompt->buffer.buffer);
}

void			edit_move(t_prompt *prompt, char buffer_char)
{
	if (buffer_char == 'C')
	{
		if (prompt->edit_from < prompt->edit_start)
			prompt->edit_from +=
			wcharlen(prompt->buffer.buffer[prompt->edit_from]);
		else if (prompt->buffer.buffer[prompt->edit_to])
			prompt->edit_to += wcharlen(prompt->buffer.buffer[prompt->edit_to]);
	}
	else if (buffer_char == 'D')
	{
		if (prompt->edit_to > prompt->edit_start)
			prompt->edit_to = prev_index(prompt, prompt->edit_to);
		else
			prompt->edit_from = prev_index(prompt, prompt->edit_from);
	}
	reprint_buffer(prompt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 23:20:00 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/28 14:01:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			search_render_found(t_prompt *prompt, char *found)
{
	buff_clear(&prompt->buffer);
	move_goto(prompt, prompt->prompt_pos);
	prompt->char_index = 0;
	prompt->buffer_index = 0;
	return (default_char_handler(prompt, found, NULL));
}

void		search_render(t_prompt *prompt)
{
	char	*s_prompt;
	t_pos	result;
	size_t	i;

	result.x = 0;
	result.y = prompt->max_pos.y - prompt->cursor_pos.y + 1;
	move_cursor((t_pos){.x = 0, .y = prompt->max_pos.y - prompt->cursor_pos.y});
	ft_dprintf(0, "\n");
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	if (prompt->search_found)
		s_prompt = "bck-i-search: ";
	else
		s_prompt = "failing bck-i-search: ";
	ft_dprintf(0, "%s", s_prompt);
	while (*s_prompt)
		transform_pos(prompt, &result, *(s_prompt++));
	ft_dprintf(0, "%s_", prompt->search_buffer.buffer);
	i = 0;
	while (i < prompt->search_buffer.size)
	{
		transform_pos(prompt, &result, prompt->search_buffer.buffer[i]);
		i += wcharlen(prompt->search_buffer.buffer[i]);
	}
	transform_pos(prompt, &result, '_');
	move_cursor((t_pos){.x = prompt->cursor_pos.x - result.x, .y = -result.y});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:02:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 20:02:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: currently unstable
*/

void			reprint_everything(t_prompt *prompt)
{
	t_pos	back;
	size_t	buffer_index_back;
	size_t	char_index_back;
	size_t	nb_lines;

	nb_lines = prompt->cursor_pos.y;
	while (nb_lines--)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	ft_putstr_fd(prompt->prompt, 0);
	back = prompt->cursor_pos;
	buffer_index_back = prompt->buffer_index;
	char_index_back = prompt->char_index;
	prompt->buffer_index = 0;
	prompt->char_index = 0;
	prompt->cursor_pos = prompt->prompt_pos;
	print_from_cursor(prompt, &back);
	prompt->buffer_index = buffer_index_back;
	prompt->char_index = char_index_back;
	if (prompt->select_mode == 1)
		select_render(prompt, &prompt->select);
}

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

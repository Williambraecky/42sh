/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:51:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/25 17:58:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: currently unstable
*/

/*
** NOTE: reprints whole buffer
*/

void	reprint_buffer(t_prompt *prompt)
{
	t_pos	new;

	move_goto(prompt, prompt->prompt_pos);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(prompt->buffer.buffer, 0);
	new = new_calc_write(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer.buffer));
	prompt->cursor_pos = new_calc(prompt,
		prompt->prompt_len + prompt->char_index);
	new.x = prompt->cursor_pos.x - new.x;
	new.y = prompt->cursor_pos.y - new.y;
	move_cursor(new);
}

/*
** NOTE: reprints from cursor
*/

void	print_from_cursor(t_prompt *prompt)
{
	t_pos	new;

	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(ft_wstrindex(prompt->buffer.buffer,
		prompt->char_index - 1), 0);
	new = new_calc_write(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer.buffer));
	prompt->cursor_pos = new_calc(prompt,
		prompt->prompt_len + prompt->char_index);
	new.x = prompt->cursor_pos.x - new.x;
	new.y = prompt->cursor_pos.y - new.y;
	move_cursor(new);
}

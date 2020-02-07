/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:53:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	handle_backspace_edit(t_prompt *prompt)
{
	(void)prompt;
	buff_nremove(&prompt->buffer, prompt->edit_from,
		prompt->edit_to - prompt->edit_from);
	prompt->edit_mode = 0;
	prompt->buffer_index = prompt->edit_from;
	prompt->char_index = ft_wstrfromindex(prompt->buffer.buffer,
		prompt->buffer_index);
	move_goto(prompt, calc_cursor_pos(prompt, prompt->char_index));
	print_from_cursor(prompt, NULL);
	return (SH_SUCCESS);
}

int			handle_backspace(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	(void)shell;
	if (prompt->edit_mode)
		return (handle_backspace_edit(prompt));
	if (prompt->char_index == 0)
		return (SH_SUCCESS);
	buff_remove(&prompt->buffer, ft_wstrindex(prompt->buffer.buffer,
		prompt->char_index - 1) - prompt->buffer.buffer);
	move_left(prompt);
	print_from_cursor(prompt, NULL);
	return (SH_SUCCESS);
}

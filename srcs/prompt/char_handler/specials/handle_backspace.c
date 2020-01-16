/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 00:29:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_backspace(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	(void)shell;
	if (prompt->char_index == 0)
		return (SH_SUCCESS);
	buff_remove(&prompt->buffer, ft_wstrindex(prompt->buffer.buffer,
		prompt->char_index - 1) - prompt->buffer.buffer);
	move_left(prompt);
	print_from_cursor(prompt, NULL);
	return (SH_SUCCESS);
}

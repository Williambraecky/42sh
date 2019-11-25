/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/25 17:40:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_backspace(t_prompt *prompt, char *buffer)
{
	(void)buffer;
	if (prompt->char_index == 0)
		return (RET_CONT);
	buff_remove(&prompt->buffer, ft_wstrindex(prompt->buffer.buffer,
		prompt->char_index - 1) - prompt->buffer.buffer);
	move_left(prompt, 1);
	return (RET_CONT | RET_REPRINT);
}

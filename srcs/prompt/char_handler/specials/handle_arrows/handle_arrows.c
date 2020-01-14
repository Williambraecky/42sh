/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 21:16:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		handle_arrows(t_prompt *prompt, char *buffer)
{
	if (buffer[1] != '[')
		return (1);
	if (buffer[2] == 'A')
		; //TODO: Move up
	else if (buffer[2] == 'B')
		; //TODO: Move down
	else if (buffer[2] == 'C')
		move_right(prompt);
	else if (buffer[2] == 'D')
		move_left(prompt);
	else if (buffer[2] == 'H' && prompt->char_index != 0)
	{
		prompt->buffer_index = 0;
		prompt->char_index = 0;
		move_goto(prompt, prompt->prompt_pos);
	}
	else if (buffer[2] == 'F')
	{
		prompt->char_index = ft_wstrlen(prompt->buffer.buffer);
		prompt->buffer_index = ft_wstrindex(prompt->buffer.buffer,
			prompt->char_index) - prompt->buffer.buffer;
		move_goto(prompt, prompt->max_pos);
	}
	return (RET_CONT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 17:52:06 by wbraeckm         ###   ########.fr       */
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
		move_right(prompt, 1); //TODO: Move left
	else if (buffer[2] == 'D')
		move_left(prompt, 1); //TODO: Move right
	else if (buffer[2] == 'H' && prompt->char_index != 0)
	{
		prompt->buffer_index = 0;
		prompt->char_index = 0;
		move_goto(prompt, prompt->prompt_pos); //TODO: home
	}
	else if (buffer[2] == 'F')
	{
		prompt->char_index = ft_wstrlen(prompt->buffer);
		prompt->buffer_index = ft_wstrindex(prompt->buffer, prompt->char_index)
									- prompt->buffer;
		move_goto(prompt, new_calc(prompt,
			prompt->prompt_len + prompt->char_index)); //TODO: end
	}
	return (RET_CONT);
}

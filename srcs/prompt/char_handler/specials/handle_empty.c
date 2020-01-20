/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:55:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/20 22:55:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: if prompt is not empty remove character the cursor is sitting on
*/

int			char_empty(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	(void)shell;
	if (prompt->buffer.size)
	{
		if (prompt->buffer.buffer[prompt->buffer_index])
			buff_remove(&prompt->buffer, ft_wstrindex(prompt->buffer.buffer,
				prompt->char_index) - prompt->buffer.buffer);
		print_from_cursor(prompt, NULL);
		return (SH_SUCCESS);
	}
	buff_clear(&prompt->buffer);
	if (buff_append(&prompt->buffer, "exit\n") != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	prompt->done = 1;
	return (SH_SUCCESS);
}

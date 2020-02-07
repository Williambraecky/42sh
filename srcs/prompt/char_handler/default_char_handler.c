/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:57:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			default_char_handler(t_prompt *prompt, char *buffer, t_sh *shell)
{
	t_pos	new;
	size_t	i;
	size_t	wlen;

	(void)shell;
	prompt->edit_mode = 0;
	if (buff_insert(&prompt->buffer, buffer, prompt->buffer_index)
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	new = prompt->cursor_pos;
	i = 0;
	wlen = 0;
	while (buffer[i])
	{
		transform_pos(prompt, &new, buffer[i]);
		i += wcharlen(buffer[i]);
		wlen++;
	}
	print_from_cursor(prompt, &new);
	prompt->buffer_index += i;
	prompt->char_index += wlen;
	return (SH_SUCCESS);
}

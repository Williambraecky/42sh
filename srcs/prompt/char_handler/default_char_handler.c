/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 16:03:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	transform_pos(t_prompt *prompt, t_pos *pos, char c)
{
	if (c == '\n')
		pos->x = prompt->winsize.ws_col;
	else if (c == '\t')
		pos->x += 8 - pos->x % 8;
	else
		pos->x++;
	if (pos->x == prompt->winsize.ws_col)
	{
		pos->x = 0;
		pos->y++;
	}
}

int			default_char_handler(t_prompt *prompt, char *buffer, t_sh *shell)
{
	t_pos	new;
	size_t	i;

	(void)shell;
	if (buff_insert(&prompt->buffer, buffer, prompt->buffer_index)
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	new = prompt->cursor_pos;
	i = 0;
	while (buffer[i])
	{
		transform_pos(prompt, &new, buffer[i]);
		i += wcharlen(buffer[i]);
	}
	print_from_cursor(prompt, &new);
	prompt->buffer_index += ft_strlen(buffer);
	prompt->char_index += ft_wstrlen(buffer);
	return (RET_CONT);
}

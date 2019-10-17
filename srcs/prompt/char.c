/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:53:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/17 17:42:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	default_char_handler(t_prompt *prompt, char *buffer)
{
	char	*result;

	if (!(result =
		ft_strinsert(prompt->buffer, buffer, prompt->buffer_index)))
	{
		ft_strdel(&prompt->buffer);
		return (RET_ERR);
	}
	ft_strdel(&prompt->buffer);
	write(0, buffer, wcharlen(*buffer));
	prompt->buffer = result;
	prompt->buffer_index += wcharlen(*buffer);
	prompt->char_index++;
	prompt->cursor_pos.x++;
	if (prompt->cursor_pos.x == prompt->winsize.ws_col)
	{
		prompt->cursor_pos.y++;
		move_cursor((t_pos){.y = 1, .x = -prompt->cursor_pos.x});
		prompt->cursor_pos.x = 0;
	}
	if (ft_wstrlen(prompt->buffer) != prompt->char_index)
		return (RET_REPRINT | RET_CONT);
	return (RET_PRINT | RET_CONT);
}

static int	handle_backspace(t_prompt *prompt, char *buffer)
{
	char	*result;

	(void)buffer;
	if (prompt->char_index == 0)
		return (RET_CONT);
	if (!(result = wstr_remove_char(prompt->buffer, prompt->char_index - 1)))
	{
		ft_strdel(&prompt->buffer);
		return (RET_ERR);
	}
	ft_strdel(&prompt->buffer);
	prompt->buffer = result;
	move_left(prompt, 1);
	return (RET_CONT | RET_REPRINT);
}

static int	handle_newline(t_prompt *prompt, char *buffer)
{
	(void)prompt;
	(void)buffer;
	return (RET_NL);
}

static int	handle_arrows(t_prompt *prompt, char *buffer)
{
	(void)prompt;
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
	return (RET_CONT);
}

int			(*g_dispatch_char[])(t_prompt *, char *buffer) =
{
	[127] = handle_backspace,
	['\t'] = handle_newline,
	['\n'] = handle_newline,
	[0x1B] = handle_arrows
};

int			handle_new_char(t_prompt *prompt, char *buffer)
{
	int		(*dispatch_func)(t_prompt *, char *buffer);

	dispatch_func = NULL;
	if ((t_u64)buffer[0] < (sizeof(g_dispatch_char) / sizeof(*g_dispatch_char)))
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer));
}

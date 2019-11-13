/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:53:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/13 16:43:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			(*g_dispatch_char[])(t_prompt *, char *buffer) =
{
	[127] = handle_backspace,
	['\t'] = handle_tab,
	['\n'] = handle_newline,
	[0x1B] = handle_escape
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

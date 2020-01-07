/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:53:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 16:44:34 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: use the main read from prompt but dispatch correctly
**    when in a tab complete
*/

int			(*g_select_dispatch[])(t_prompt *, char *buffer, t_sh *shell) =
{
	['\n'] = select_handle_newline,
	[0x1B] = select_handle_escape,
	['\t'] = select_handle_tab,
	[127] = NULL,
};

int			(*g_dispatch_char[])(t_prompt *, char *buffer, t_sh *shell) =
{
	[127] = handle_backspace,
	['\t'] = handle_tab,
	['\n'] = handle_newline,
	[0x1B] = handle_escape
};

static int	handle_select_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *buffer, t_sh *shell);

	dispatch_func = NULL;
	if ((t_u64)buffer[0] <
		(sizeof(g_select_dispatch) / sizeof(*g_select_dispatch)))
		dispatch_func = g_select_dispatch[(int)*buffer];
	if (dispatch_func)
		return (dispatch_func(prompt, buffer, shell));
	return (RET_EXIT_SELECT);
}

int			handle_new_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *buffer, t_sh *shell);
	int		ret;

	dispatch_func = NULL;
	if (prompt->select_mode == 2 &&
		(ret = handle_select_char(prompt, buffer, shell)) != RET_EXIT_SELECT)
		return (ret);
	if (prompt->select_mode == 2 ||
		(prompt->select_mode == 1 && *buffer != '\t'))
	{
		prompt->select_mode = 0;
		ft_vecfree(&prompt->select.poss);
	}
	if ((t_u64)buffer[0] < (sizeof(g_dispatch_char) / sizeof(*g_dispatch_char)))
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer, shell));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:53:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 03:14:58 by wbraeckm         ###   ########.fr       */
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

static int	char_ignore(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)prompt;
	(void)buffer;
	(void)shell;
	return (SH_SUCCESS);
}

/*
** NOTE: if prompt is not empty remove character the cursor is sitting on
*/

static int	char_empty(t_prompt *prompt, char *buffer, t_sh *shell)
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

/*
** TODO: some characters are just to be ignored
*/

int			(*g_dispatch_char[])(t_prompt *, char *buffer, t_sh *shell) =
{
	[0] = char_ignore,
	[1] = char_ignore,
	[2] = char_ignore,
	[3] = char_ignore,
	[4] = char_empty,
	[5] = char_ignore,
	[6] = char_ignore,
	[7] = char_ignore,
	[8] = char_ignore,
	[11] = char_ignore,
	[12] = char_ignore,
	[13] = char_ignore,
	[14] = char_ignore,
	[15] = char_ignore,
	[16] = char_ignore,
	[17] = char_ignore,
	[18] = char_ignore,
	[19] = char_ignore,
	[20] = char_ignore,
	[21] = char_ignore,
	[22] = char_ignore,
	[23] = char_ignore,
	[24] = char_ignore,
	[25] = char_ignore,
	[26] = char_ignore,
	[28] = char_ignore,
	[29] = char_ignore,
	[30] = char_ignore,
	[31] = char_ignore,
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
	return (PROMPT_EXIT_SELECT);
}

static void	finish_query(t_prompt *prompt)
{
	ft_strdel(&prompt->query.query);
	ft_strdel(&prompt->query.orig);
	prompt->querying = 0;
}

int			handle_new_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *buffer, t_sh *shell);
	int		ret;

	dispatch_func = NULL;
	if (*buffer != '\e')
		prompt->nl_offset = -1;
	if (prompt->querying && *((int*)buffer) != UP_ARROW &&
		*((int*)buffer) != DOWN_ARROW)
		finish_query(prompt);
	if (prompt->select_mode == 2 &&
		(ret = handle_select_char(prompt, buffer, shell)) != PROMPT_EXIT_SELECT)
		return (ret);
	if (prompt->select_mode == 2 ||
		(prompt->select_mode == 1 && *buffer != '\t'))
	{
		prompt->select_mode = 0;
		ft_vecdestroy(&prompt->select.poss, default_vec_destroy_function);
	}
	if ((t_u64)buffer[0] < (sizeof(g_dispatch_char) / sizeof(*g_dispatch_char)))
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer, shell));
}

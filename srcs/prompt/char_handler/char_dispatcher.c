/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:53:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 23:52:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int		(*g_select_dispatch[])(t_prompt *, char *, t_sh *) =
{
	['\n'] = select_handle_newline,
	[0x1B] = select_handle_escape,
	['\t'] = select_handle_tab
};

static size_t	g_select_size =
	(sizeof(g_select_dispatch) / sizeof(*g_select_dispatch));


static int		(*g_search_dispatch[])(t_prompt *, char *, t_sh *) =
{
	[18] = handle_search,
	[32 ... 126] = handle_char_search,
	[127] = handle_backspace_search,
};

static size_t	g_search_size =
	(sizeof(g_search_dispatch) / sizeof(*g_search_dispatch));

/*
** TODO: some characters are just to be ignored
*/

static int		(*g_dispatch_char[])(t_prompt *, char *, t_sh *) =
{
	[0 ... 3] = char_ignore,
	[4] = char_empty,
	[5 ... 8] = char_ignore,
	['\t'] = handle_tab,
	['\n'] = handle_newline,
	[11 ... 17] = char_ignore,
	[18] = handle_search,
	[19 ... 26] = char_ignore,
	[27] = handle_escape,
	[28 ... 31] = char_ignore,
	[127] = handle_backspace,
};

static size_t	g_dispatch_size =
	(sizeof(g_dispatch_char) / sizeof(*g_dispatch_char));

static void	finish_query(t_prompt *prompt)
{
	ft_strdel(&prompt->query.query);
	ft_strdel(&prompt->query.orig);
	prompt->querying = 0;
}

static int	handle_select_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *, t_sh *);

	dispatch_func = NULL;
	if (prompt->select_mode == 1 && *buffer == '\t')
		dispatch_func = handle_tab;
	else if (prompt->select_mode == 2 && (t_u64)buffer[0] < g_select_size)
		dispatch_func = g_select_dispatch[(int)*buffer];
	if (dispatch_func)
		return (dispatch_func(prompt, buffer, shell));
	prompt->select_mode = 0;
	ft_vecdestroy(&prompt->select.poss, default_vec_destroy_function);
	if ((t_u64)buffer[0] < g_dispatch_size)
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer, shell));
}

static int	handle_search_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *, t_sh *);

	dispatch_func = NULL;
	if ((t_u64)buffer[0] < g_search_size)
		dispatch_func = g_search_dispatch[(int)*buffer];
	if (dispatch_func)
		return (dispatch_func(prompt, buffer, shell));
	prompt->searching = 0;
	ft_strdel(&prompt->query.orig);
	if ((t_u64)buffer[0] < g_dispatch_size)
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer, shell));
}

int			handle_new_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *, t_sh *);

	dispatch_func = NULL;
	if (*buffer != '\e')
		prompt->nl_offset = -1;
	if (prompt->querying && *((int*)buffer) != UP && *((int*)buffer) != DOWN)
		finish_query(prompt);
	if (prompt->select_mode != 0)
		return (handle_select_char(prompt, buffer, shell));
	else if (prompt->searching)
		return (handle_search_char(prompt, buffer, shell));
	if ((t_u64)buffer[0] < g_dispatch_size)
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer, shell));
}

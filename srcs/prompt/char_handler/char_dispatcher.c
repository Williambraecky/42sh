/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:53:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:47:29 by wbraeckm         ###   ########.fr       */
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
	[32] = handle_char_search,
	[33] = handle_char_search,
	[34] = handle_char_search,
	[35] = handle_char_search,
	[36] = handle_char_search,
	[37] = handle_char_search,
	[38] = handle_char_search,
	[39] = handle_char_search,
	[40] = handle_char_search,
	[41] = handle_char_search,
	[42] = handle_char_search,
	[43] = handle_char_search,
	[44] = handle_char_search,
	[45] = handle_char_search,
	[46] = handle_char_search,
	[47] = handle_char_search,
	[48] = handle_char_search,
	[49] = handle_char_search,
	[50] = handle_char_search,
	[51] = handle_char_search,
	[52] = handle_char_search,
	[53] = handle_char_search,
	[54] = handle_char_search,
	[55] = handle_char_search,
	[56] = handle_char_search,
	[57] = handle_char_search,
	[58] = handle_char_search,
	[59] = handle_char_search,
	[60] = handle_char_search,
	[61] = handle_char_search,
	[62] = handle_char_search,
	[63] = handle_char_search,
	[64] = handle_char_search,
	[65] = handle_char_search,
	[66] = handle_char_search,
	[67] = handle_char_search,
	[68] = handle_char_search,
	[69] = handle_char_search,
	[70] = handle_char_search,
	[71] = handle_char_search,
	[72] = handle_char_search,
	[73] = handle_char_search,
	[74] = handle_char_search,
	[75] = handle_char_search,
	[76] = handle_char_search,
	[77] = handle_char_search,
	[78] = handle_char_search,
	[79] = handle_char_search,
	[80] = handle_char_search,
	[81] = handle_char_search,
	[82] = handle_char_search,
	[83] = handle_char_search,
	[84] = handle_char_search,
	[85] = handle_char_search,
	[86] = handle_char_search,
	[87] = handle_char_search,
	[88] = handle_char_search,
	[89] = handle_char_search,
	[90] = handle_char_search,
	[91] = handle_char_search,
	[92] = handle_char_search,
	[93] = handle_char_search,
	[94] = handle_char_search,
	[95] = handle_char_search,
	[96] = handle_char_search,
	[97] = handle_char_search,
	[98] = handle_char_search,
	[99] = handle_char_search,
	[100] = handle_char_search,
	[101] = handle_char_search,
	[102] = handle_char_search,
	[103] = handle_char_search,
	[104] = handle_char_search,
	[105] = handle_char_search,
	[106] = handle_char_search,
	[107] = handle_char_search,
	[108] = handle_char_search,
	[109] = handle_char_search,
	[110] = handle_char_search,
	[111] = handle_char_search,
	[112] = handle_char_search,
	[113] = handle_char_search,
	[114] = handle_char_search,
	[115] = handle_char_search,
	[116] = handle_char_search,
	[117] = handle_char_search,
	[118] = handle_char_search,
	[119] = handle_char_search,
	[120] = handle_char_search,
	[121] = handle_char_search,
	[122] = handle_char_search,
	[123] = handle_char_search,
	[124] = handle_char_search,
	[125] = handle_char_search,
	[126] = handle_char_search,
	[127] = handle_backspace_search,
};

static size_t	g_search_size =
	(sizeof(g_search_dispatch) / sizeof(*g_search_dispatch));

static int		(*g_dispatch_char[])(t_prompt *, char *, t_sh *) =
{
	[0] = char_ignore,
	[1] = char_ignore,
	[2] = char_ignore,
	[3] = char_ignore,
	[4] = char_empty,
	[5] = handle_edit,
	[6] = char_ignore,
	[7] = char_ignore,
	[8] = char_ignore,
	['\t'] = handle_tab,
	['\n'] = handle_newline,
	[11] = char_ignore,
	[12] = char_ignore,
	[13] = char_ignore,
	[14] = char_ignore,
	[15] = char_ignore,
	[16] = handle_paste,
	[17] = char_ignore,
	[18] = handle_search,
	[19] = char_ignore,
	[20] = char_ignore,
	[21] = char_ignore,
	[22] = char_ignore,
	[23] = char_ignore,
	[24] = char_ignore,
	[25] = char_ignore,
	[26] = char_ignore,
	[27] = handle_escape,
	[28] = char_ignore,
	[29] = char_ignore,
	[30] = char_ignore,
	[31] = char_ignore,
	[127] = handle_backspace,
};

static size_t	g_dispatch_size =
	(sizeof(g_dispatch_char) / sizeof(*g_dispatch_char));

static int		(*g_edit_dispatch[])(t_prompt *, char *, t_sh *) =
{
	[5] = handle_edit,
	[21] = handle_copy,
	[24] = handle_cut,
	[27] = handle_escape,
	[127] = handle_backspace,
};

static size_t	g_edit_size =
	(sizeof(g_edit_dispatch) / sizeof(*g_edit_dispatch));

static void	finish_query(t_prompt *prompt)
{
	ft_strdel(&prompt->query.query);
	ft_strdel(&prompt->query.orig);
	prompt->querying = 0;
}

static int	handle_select_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *, t_sh *);
	int		ret;

	dispatch_func = NULL;
	if (prompt->select_mode == 1 && *buffer == '\t')
		dispatch_func = handle_tab;
	else if (prompt->select_mode == 2 && (t_u64)buffer[0] < g_select_size)
		dispatch_func = g_select_dispatch[(int)*buffer];
	if (dispatch_func &&
		(ret = dispatch_func(prompt, buffer, shell)) != PROMPT_EXIT_SELECT)
		return (ret);
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

static int	handle_edit_char(t_prompt *prompt, char *buffer, t_sh *shell)
{
	int		(*dispatch_func)(t_prompt *, char *, t_sh *);

	dispatch_func = NULL;
	if ((t_u64)buffer[0] < g_edit_size)
		dispatch_func = g_edit_dispatch[(int)*buffer];
	if (dispatch_func)
		return (dispatch_func(prompt, buffer, shell));
	handle_backspace(prompt, buffer, shell);
	prompt->edit_mode = 0;
	reprint_buffer(prompt);
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
	else if (prompt->edit_mode)
		return (handle_edit_char(prompt, buffer, shell));
	if ((t_u64)buffer[0] < g_dispatch_size)
		dispatch_func = g_dispatch_char[(int)*buffer];
	if (dispatch_func == NULL)
		dispatch_func = default_char_handler;
	return (dispatch_func(prompt, buffer, shell));
}

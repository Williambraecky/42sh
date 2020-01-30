/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:37:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 22:59:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: Main prompt generation procedure
*/

int		gen_prompt(t_sh *shell, char *prompt_str, t_prompt *prompt)
{
	if (shell->interactive_mode)
		tcsetattr(SH_IN, TCSADRAIN, &shell->current_termios);
	if (!(prompt->prompt = ft_strdup(prompt_str)))
		return (SH_ERR_MALLOC);
	if (!get_cursor_pos(shell, &prompt->cursor_pos.x, &prompt->cursor_pos.y))
		prompt->valid_pos = 1;
	if (buff_init(&prompt->buffer) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	if (buff_init(&prompt->search_buffer) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	prompt->nl_offset = -1;
	if (!gettermsize(&prompt->winsize))
		prompt->valid_size = 1;
	return (0);
}

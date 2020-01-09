/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:37:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/09 14:22:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: Main prompt generation procedure
*/

int		gen_prompt(t_sh *shell, char *prompt_str, t_prompt *prompt)
{
	if (!(prompt->prompt = ft_strdup(prompt_str)))
		return (SH_ERR_MALLOC);
	if (!get_cursor_pos(shell, &prompt->cursor_pos.x, &prompt->cursor_pos.y))
		prompt->valid_pos = 1;
	if (!(prompt->buffer.buffer = ft_strnew(PBUFF_DEF_SIZE)))
		return (SH_ERR_MALLOC);
	prompt->buffer.max_size = PBUFF_DEF_SIZE;
	if (!gettermsize(&prompt->winsize))
		prompt->valid_size = 1;
	return (0);
}

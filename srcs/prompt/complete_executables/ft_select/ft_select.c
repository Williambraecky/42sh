/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:06:10 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/07 18:31:44 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt)
{
	(void)shell;
	ft_memset(&prompt->select, 0, sizeof(prompt->select));
	prompt->select.poss = *poss;
	get_display_info(&prompt->select, prompt);
	prompt->select_mode = 1;
	prompt->select.pos_col = 0;
	prompt->select.selected = -1;
//	prompt->select.written = ft_strlen(get_last_word(prompt->buffer.buffer, NULL));
	prompt->select.original_pos = prompt->cursor_pos;
	select_render(prompt, &prompt->select);
	return (SH_SUCCESS);
}

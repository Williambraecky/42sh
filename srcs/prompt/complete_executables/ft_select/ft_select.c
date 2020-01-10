/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:06:10 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/09 20:03:21 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt)
{
	int right;
	int left;
	int file_complete;
	(void)shell;

	right = prompt->select.cursor_right_len;
	left = prompt->select.cursor_left_len;
	file_complete = prompt->select.file_complete;
	ft_memset(&prompt->select, 0, sizeof(prompt->select));
	prompt->select.poss = *poss;
	get_display_info(&prompt->select, prompt);
	prompt->select_mode = 1;
	prompt->select.selected = -1;
	prompt->select.original_pos = prompt->cursor_pos;
	prompt->select.cursor_right_len = right;
	prompt->select.cursor_left_len = left;
	prompt->select.file_complete = file_complete;
	select_render(prompt, &prompt->select);
	return (SH_SUCCESS);
}

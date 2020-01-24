/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:06:10 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/24 19:10:02 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt)
{
	int right;
	int left;
	int shell_var_brace;
	int file_complete;

	(void)shell;
	right = prompt->select.cursor_right_len;
	left = prompt->select.cursor_left_len;
	shell_var_brace = prompt->select.shell_var_brace;
	file_complete = prompt->select.file_complete;
	ft_memset(&prompt->select, 0, sizeof(prompt->select));
	prompt->select.poss = *poss;
	get_display_info(&prompt->select, prompt);
	prompt->select_mode = 1;
	prompt->select.selected = -1;
	prompt->select.original_pos = prompt->cursor_pos;
	prompt->select.cursor_right_len = right;
	prompt->select.cursor_left_len = left;
	prompt->select.shell_var_brace = shell_var_brace;
	prompt->select.file_complete = file_complete;
	prompt->select.scroll_top = 0;
	prompt->select.scroll_bottom =
		prompt->select.nb_row - prompt->max_pos.y - 1;
	select_render(prompt, &prompt->select);
	return (SH_SUCCESS);
}

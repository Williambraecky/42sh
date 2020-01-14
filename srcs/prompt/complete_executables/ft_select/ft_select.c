/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:06:10 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/14 16:27:34 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt)
{
	int right;
	int left;
	int shell_var_brace;
	int command_complete;

	(void)shell;
	right = prompt->select.cursor_right_len;
	left = prompt->select.cursor_left_len;
	shell_var_brace = prompt->select.shell_var_brace;
	command_complete = prompt->select.command_complete;
	ft_memset(&prompt->select, 0, sizeof(prompt->select));
	prompt->select.poss = *poss;
	get_display_info(&prompt->select, prompt);
	prompt->select_mode = 1;
	prompt->select.selected = -1;
	prompt->select.original_pos = prompt->cursor_pos;
	prompt->select.cursor_right_len = right;
	prompt->select.cursor_left_len = left;
	prompt->select.shell_var_brace = shell_var_brace;
	prompt->select.command_complete = command_complete;
	select_render(prompt, &prompt->select);
	return (SH_SUCCESS);
}

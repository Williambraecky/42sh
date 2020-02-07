/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:17:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:17:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_edit(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	(void)shell;
	prompt->edit_mode ^= 1;
	prompt->edit_start = prompt->buffer_index;
	prompt->edit_from = prompt->buffer_index;
	prompt->edit_to = prompt->buffer_index;
	reprint_buffer(prompt);
	return (SH_SUCCESS);
}

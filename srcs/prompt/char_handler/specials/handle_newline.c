/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 19:56:43 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: this should validate the selection and clear the screen of it
*/

int	erase_poss(t_prompt *prompt)
{
	t_pos pos;

	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
//	ft_putstr_fd(tgetstr("cr", NULL), 0); //maybe useless
	pos.x = prompt->cursor_pos.x;
	pos.y = -1;
	move_cursor(pos);
	return (SH_SUCCESS);
}

int	select_handle_newline(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)shell;
	(void)buffer;
	t_select *select;

	select = &prompt->select;
	prompt->select_mode = 0;
	erase_poss(prompt);
	default_char_handler(prompt, " ", NULL);
	return (RET_CONT);
}

int	handle_newline(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	(void)shell;
	if (buff_insert(&prompt->buffer, "\n", ft_strlen(prompt->buffer.buffer))
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (RET_NL);
}

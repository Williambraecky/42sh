/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:37:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/16 19:32:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: Main prompt generation procedure
*/

int		gen_prompt(t_sh *shell, t_prompt *prompt)
{
	char	*pwd_short;

	pwd_short = getpwd_short(shell);
	if (!(prompt->prompt = ft_strformat("{cyan}%s{eoc} > ", pwd_short)))
		return (1);
	free(pwd_short);
	if (!get_cursor_pos(shell, &prompt->cursor_pos.x, &prompt->cursor_pos.y))
		prompt->valid_pos = 1;
	if (!(prompt->buffer = ft_strnew(0)))
		return (1);
	if (!gettermsize(&prompt->winsize))
		prompt->valid_size = 1;
	return (0);
}

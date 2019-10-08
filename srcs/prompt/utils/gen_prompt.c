/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:37:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 17:07:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: Main prompt generation procedure
*/

int		gen_prompt(t_sh *shell, t_prompt *prompt)
{
	prompt->prompt = ft_strdup("21sh >");
	if (!get_cursor_pos(shell, &prompt->cursor_pos.x, &prompt->cursor_pos.y))
		prompt->valid_pos = 1;
	return (0);
}

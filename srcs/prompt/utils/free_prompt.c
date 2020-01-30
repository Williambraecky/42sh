/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:37:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 22:59:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	free_prompt(t_sh *shell, t_prompt *prompt)
{
	ft_strdel(&prompt->query.query);
	ft_strdel(&prompt->query.orig);
	ft_strdel(&prompt->prompt);
	ft_strdel(&prompt->search_buffer.buffer);
	if (prompt->select.poss.vec)
		ft_vecfree(&prompt->select.poss);
	if (shell->interactive_mode)
		tcsetattr(SH_IN, TCSADRAIN, &shell->old_termios);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:19:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:20:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		handle_copy(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)shell;
	(void)buffer;
	if (prompt->clipboard)
		ft_strdel(&prompt->clipboard);
	if (!(prompt->clipboard =
		ft_strndup(prompt->buffer.buffer + prompt->edit_from,
		prompt->edit_to - prompt->edit_from)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

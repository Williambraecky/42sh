/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 00:14:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: this should validate the selection and clear the screen of it
*/

int	select_handle_newline(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)prompt;
	(void)buffer;
	(void)shell;
	return (SH_SUCCESS);
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

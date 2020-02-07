/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:15:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:16:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_paste(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	(void)shell;
	if (!prompt->clipboard)
		return (SH_SUCCESS);
	return (default_char_handler(prompt, prompt->clipboard, shell));
}

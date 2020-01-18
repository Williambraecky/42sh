/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:59:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 22:08:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	select_handle_escape(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)shell;
	if (buffer[1] == '[')
		return (select_handle_arrows(prompt, buffer));
	return (PROMPT_EXIT_SELECT);
}

int	handle_escape(t_prompt *prompt, char *buffer, t_sh *shell)
{
	if (buffer[1] == '[')
		return (handle_arrows(prompt, buffer, shell));
	else if (buffer[1] == '\e' && buffer[2] == '[')
		return (handle_shift_arrows(prompt, buffer, shell));
	else if (ft_isprint(*(buffer + 1)) || *(buffer + 1) == '\n')
		return (default_char_handler(prompt, buffer + 1, shell));
	return (SH_SUCCESS);
}

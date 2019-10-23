/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:59:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 16:30:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_escape(t_prompt *prompt, char *buffer)
{
	if (buffer[1] == '[')
		return (handle_arrows(prompt, buffer));
	else if (buffer[1] == '\n')
		return (default_char_handler(prompt, "\n"));
	return (RET_CONT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:59:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/25 18:37:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_escape(t_prompt *prompt, char *buffer)
{
	if (buffer[1] == '[')
		return (handle_arrows(prompt, buffer));
	else if (ft_isprint(*(buffer + 1)))
		return (default_char_handler(prompt, buffer + 1));
	return (RET_CONT);
}

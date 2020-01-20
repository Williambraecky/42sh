/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ignore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:55:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/20 22:55:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			char_ignore(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)prompt;
	(void)buffer;
	(void)shell;
	return (SH_SUCCESS);
}

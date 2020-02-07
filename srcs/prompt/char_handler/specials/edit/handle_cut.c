/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:21:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:42:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		handle_cut(t_prompt *prompt, char *buffer, t_sh *shell)
{
	if (handle_copy(prompt, buffer, shell) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (handle_backspace(prompt, buffer, shell));
}

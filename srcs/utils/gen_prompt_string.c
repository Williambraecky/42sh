/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:41:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/09 14:28:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** TODO: should we implement something like this or hardcode the prompt?
** NOTE: main procedure for substituting PS1
** NOTE: not as fancy as bash's; handles \h \H \u \w \W
*/

int		gen_prompt_string(t_sh *shell, char *ps1, char **result)
{
	(void)shell;
	(void)ps1;
	(void)result;
	return (SH_ERR_MALLOC);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:41:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 13:17:49 by wbraeckm         ###   ########.fr       */
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
	char	*prompt;
	char	*tmp;

	(void)ps1;
	prompt = getpwd_short(shell);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "> ");
	free(tmp);
	*result = prompt;
	return (SH_SUCCESS);
}

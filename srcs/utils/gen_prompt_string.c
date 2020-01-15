/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:41:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 14:58:11 by ntom             ###   ########.fr       */
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
	int		ret;

	ret = SH_SUCCESS;
	if (ps1 == NULL)
		prompt = ft_strdup("");
	else
		ret = expand_param(shell, ps1, &prompt);
	if (ret != SH_SUCCESS)
		return (ret);
	if (!prompt)
		return (SH_ERR_MALLOC);
	*result = prompt;
	return (SH_SUCCESS);
}

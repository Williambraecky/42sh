/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:28:16 by ntom              #+#    #+#             */
/*   Updated: 2020/01/15 17:28:45 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			is_valid_esc(char *prompt, size_t *i)
{
	return ((prompt[*i] == '\\' && !is_char_escaped(prompt, *i)
	&& (prompt[++(*i)] == 'h' || prompt[*i] == 'H'
	|| prompt[*i] == 'w' || prompt[*i] == 'W' || prompt[*i] == 'u')));
}

int			end_gen_prompt(int ret, char **result, char *prompt)
{
	if (ret != SH_SUCCESS)
		return (ret);
	*result = prompt;
	return ((*result) ? SH_SUCCESS : SH_ERR_MALLOC);
}

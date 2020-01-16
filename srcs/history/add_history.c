/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 02:41:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 03:01:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

/*
** TODO: do not add if empty or if last line was the same
*/

int			add_history(t_sh *shell, char *str)
{
	char	*top;

	if (check_empty(str))
		return (SH_SUCCESS);
	top = ft_vecgettop(&shell->history);
	str[ft_strlen(str) - 1] = '\0';
	if (top && ft_strequ(str, top))
		return (SH_SUCCESS);
	ft_vecpush(&shell->history, ft_strdup(str));
	return (SH_SUCCESS);
}

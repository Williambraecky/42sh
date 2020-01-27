/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 02:41:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:03:44 by wbraeckm         ###   ########.fr       */
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

static int	add_to_file(t_sh *shell, char *str)
{
	char	*replaced;

	if (shell->history_file <= 0)
		return (SH_SUCCESS);
	if (!(replaced = ft_strsreplall(str, "\n", "\\\n")))
		return (SH_ERR_MALLOC);
	ft_dprintf(shell->history_file, "%s\n", replaced);
	free(replaced);
	return (SH_SUCCESS);
}

int			add_history(t_sh *shell, char *str)
{
	char	*top;
	char	*dup;

	if (shell->block_history)
		return (SH_SUCCESS);
	if (check_empty(str))
		return (SH_SUCCESS);
	top = ft_vecgettop(&shell->history);
	str[ft_strlen(str) - 1] = '\0';
	if (top && ft_strequ(str, top))
		return (SH_SUCCESS);
	if (!(dup = ft_strdup(str)))
		return (SH_ERR_MALLOC);
	if (add_to_file(shell, str) != SH_SUCCESS ||
		ft_vecpush(&shell->history, ft_strdup(str)))
	{
		free(dup);
		return (SH_ERR_MALLOC);
	}
	free(dup);
	return (SH_SUCCESS);
}

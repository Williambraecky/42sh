/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_handle_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:48:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 03:14:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int			willifc_handle_s(t_sh *shell, t_fc *fc)
{
	char	*equal;
	char	*tmp;
	char	*command;

	if (!(command = ft_strdup(ft_vecget(&shell->history, fc->first))) ||
		willifc_ensure_newline(&command))
	{
		ft_dprintf(2, "42sh: fc: malloc error\n");
		return (1);
	}
	if (command && fc->s_replace && (equal = ft_strchr(fc->s_replace, '=')))
	{
		tmp = command;
		*equal = '\0';
		command = ft_strsrepl(command, fc->s_replace, equal + 1);
		free(tmp);
	}
	if (command)
	{
		ft_printf("%s", command);
		run_command(shell, command);
	}
	free(command);
	return (get_last_return_code(shell));
}

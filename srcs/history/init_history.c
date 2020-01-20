/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:51:59 by ntom              #+#    #+#             */
/*   Updated: 2020/01/21 00:56:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** TODO: strsreplall is not good here it will replace \\\n if there are more lines
*/

static int	read_history_file(t_sh *shell)
{
	char	*gnl;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	while (get_next_line(shell->history_file, &gnl) == 1)
	{
		if (gnl[ft_strlen(gnl) - 1] == '\\' || tmp)
		{
			tmp2 = tmp;
			if (tmp)
				tmp = ft_strtrijoin(tmp, "\n", gnl);
			else
				tmp = ft_strdup(gnl);
			free(tmp2);
			if (gnl[ft_strlen(gnl) - 1] == '\\')
			{
				free(gnl);
				continue ;
			}
			tmp2 = tmp;
			tmp = ft_strsreplall(tmp, "\\\n", "\n");
			free(tmp2);
		}
		else
			tmp = ft_strdup(gnl);
		free(gnl);
		if (!tmp || ft_vecpush(&shell->history, tmp))
			return (SH_ERR_MALLOC);
		tmp = NULL;
	}
	return (SH_SUCCESS);
}

static int	open_history_file(t_sh *shell)
{
	char	path[PATH_MAX + 1];
	char	*home;
	int		fd;

	path[0] = '\0';
	if (get_internal(shell, "HISTFILE", &home) == SH_SUCCESS &&
		(fd = open(path, O_CREAT | O_APPEND | O_RDWR, 0666)) != -1)
		return (fd);
	if (get_env(shell, "HOME", &home) != SH_SUCCESS)
		return (-1);
	ft_strlcat(path, home, PATH_MAX + 1);
	if (path[0] && path[ft_strlen(path) - 1] != '/')
		ft_strlcat(path, "/", PATH_MAX + 1);
	ft_strlcat(path, ".willish_history", PATH_MAX + 1);
	if ((fd = open(path, O_CREAT | O_APPEND | O_RDWR, 0666)) == -1)
		return (-1);
	add_internal(shell, "HISTFILE", path);
	return (fd);
}

int			init_history(t_sh *shell)
{
	shell->history_file = open_history_file(shell);
	if (ft_vecinit(&shell->history))
		return (SH_ERR_MALLOC);
	if (shell->history_file > 0 && read_history_file(shell))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

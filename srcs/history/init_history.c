/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:51:59 by ntom              #+#    #+#             */
/*   Updated: 2020/01/27 22:50:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	read_history_handle_new_line(t_sh *shell, char *gnl, char **tmp)
{
	char	*tmp2;
	int		esc;

	if ((esc = (gnl[0] != '\0' && gnl[ft_strlen(gnl) - 1] == '\\')) || *tmp)
	{
		if (esc)
			gnl[ft_strlen(gnl) - 1] = '\0';
		tmp2 = *tmp;
		*tmp = *tmp ? ft_strtrijoin(*tmp, "\n", gnl) : ft_strdup(gnl);
		free(tmp2);
		if (esc)
		{
			free(gnl);
			return (SH_SUCCESS);
		}
	}
	else
		*tmp = ft_strdup(gnl);
	free(gnl);
	if (!*tmp || ft_vecpush(&shell->history, *tmp))
		return (SH_ERR_MALLOC);
	*tmp = NULL;
	return (SH_SUCCESS);
}

static int	read_history_file(t_sh *shell)
{
	char	*gnl;
	char	*tmp;
	int		ret;

	tmp = NULL;
	while (get_next_line(shell->history_file, &gnl) == 1)
	{
		if ((ret = read_history_handle_new_line(shell, gnl, &tmp))
			!= SH_SUCCESS)
			return (ret);
	}
	return (SH_SUCCESS);
}

static int	open_history_file(t_sh *shell)
{
	char	path[PATH_MAX + 1];
	char	*home;
	int		fd;

	path[0] = '\0';
	if (get_var(shell, "HISTFILE", &home) == SH_SUCCESS &&
		(fd = open(path, O_CREAT | O_APPEND | O_RDWR, 0666)) != -1)
		return (fd);
	if (get_var(shell, "HOME", &home) != SH_SUCCESS)
		return (-1);
	ft_strlcat(path, home, PATH_MAX + 1);
	if (path[0] && path[ft_strlen(path) - 1] != '/')
		ft_strlcat(path, "/", PATH_MAX + 1);
	ft_strlcat(path, ".willish_history", PATH_MAX + 1);
	if ((fd = open(path, O_CREAT | O_APPEND | O_RDWR, 0666)) == -1)
		return (-1);
	add_var(shell, "HISTFILE", path);
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

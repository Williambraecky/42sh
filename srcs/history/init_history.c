/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:51:59 by ntom              #+#    #+#             */
/*   Updated: 2019/10/22 18:12:59 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		init_history(t_sh *shell)
{
	int		fd;
	char	*line;
	char	*home_cont;
	char	buff[PATH_MAX + 1];

	fd = 0;
	ft_vecinit(&shell->history);
	line = NULL;
	home_cont = NULL;
	buff[0] = '\0';
	if (get_env(shell, "HOME", &home_cont) != SH_SUCCESS)
		return (SH_ERR_NOEXIST);
	ft_strlcat(buff, home_cont, PATH_MAX);
	ft_strlcat(buff, "/.42sh_history", PATH_MAX);
	fd = open(buff, O_RDWR);
	while (get_next_line(fd, &line) > 0)
		if (ft_vecpush(&shell->history, (void *)line) != 0)
			return (SH_ERR_MALLOC);
	close(fd);
	return (SH_SUCCESS);
}

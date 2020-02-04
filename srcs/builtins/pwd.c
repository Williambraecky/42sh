/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:24:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/04 18:10:24 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <sys/param.h>

/*
** NOTE: simply prints pwd; should use from env but if it's not present getcwd
*/

int		pwd_builtin(int argc, char **argv, t_sh *shell)
{
	char		*pwd;
	char		buffer[MAXPATHLEN + 1];
	t_stat		stat_t;

	(void)argc;
	(void)argv;
	buffer[0] = '\0';
	pwd = NULL;
	if (get_var(shell, "PWD", &pwd) == SH_SUCCESS && access(pwd, F_OK) == 0)
		ft_strlcat(buffer, pwd, MAXPATHLEN + 1);
	else
	{
		if (!getcwd(buffer, MAXPATHLEN + 1))
		{
			ft_dprintf(2, "pwd: getcwd error\n");
			return (1);
		}
	}
	if (stat(buffer, &stat_t) == -1)
	{
		ft_dprintf(2, "pwd: %s: No such file or directory\n", buffer);
		return (1);
	}
	ft_printf("%s\n", buffer);
	return (0);
}

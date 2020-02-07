/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:43:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 19:46:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** Function returns the last part of a pwd
** ex: /tmp -> /tmp
** ~/Documents -> Documents
*/

char	*getpwd_short(t_sh *shell)
{
	char	*pwd;
	char	*home;
	char	*short_pwd;
	char	*last;

	if (!(pwd = getpwd(shell)))
		return (NULL);
	if (get_var(shell, "HOME", &home) == SH_SUCCESS && ft_strequ(pwd, home))
	{
		free(pwd);
		return (ft_strdup("~"));
	}
	last = ft_strrchr(pwd, '/');
	if (!last)
		short_pwd = ft_strdup(pwd);
	else if (last == pwd)
		short_pwd = ft_strdup(last);
	else
		short_pwd = ft_strdup(last + 1);
	free(pwd);
	return (short_pwd);
}

char	*getpwd(t_sh *shell)
{
	char	*pwd;

	if (get_var_clone(shell, "PWD", &pwd) == SH_SUCCESS)
		return (pwd);
	return (getcwd(NULL, PATH_MAX));
}

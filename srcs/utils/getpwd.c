/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:43:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 01:57:02 by wbraeckm         ###   ########.fr       */
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
	char	*short_pwd;
	char	*last;

	if (!(pwd = getpwd(shell)))
		return (NULL);
	last = ft_strrchr(pwd, '/');
	if (last == pwd)
		short_pwd = ft_strdup(last);
	else
		short_pwd = ft_strdup(last + 1);
	free(pwd);
	return (short_pwd);
}

char	*getpwd(t_sh *shell)
{
	char	*pwd;

	if (!get_env_clone(shell, "PWD", &pwd))
		return (pwd);
	return (getcwd(NULL, PATH_MAX));
}

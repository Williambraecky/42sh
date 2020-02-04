/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 21:35:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:11:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtin.h"
#include <sys/param.h>
#include <sys/stat.h>

static int	cd_check_access(char *curpath, char *operand)
{
	struct stat	st;

	if (stat(curpath, &st) == -1)
		return (ft_dprintf(2, "42sh: cd: %s: No such file or directory\n",
		operand));
	else if (access(curpath, R_OK) == -1)
		return (ft_dprintf(2, "42sh: cd: %s: Permission denied\n", operand));
	else if (!S_ISDIR(st.st_mode))
		return (ft_dprintf(2, "42sh: cd: %s: Not a directory\n", operand));
	return (0);
}

static int	change_envs(char *curpath, int pflag, t_sh *shell)
{
	char	*old_pwd;

	if (get_var(shell, "PWD", &old_pwd) == SH_SUCCESS)
		if (repl_var(shell, "OLDPWD", old_pwd) != SH_SUCCESS)
			return (SH_ERR_MALLOC);
	if (pflag)
		getcwd(curpath, MAXPATHLEN * 2);
	return (repl_var(shell, "PWD", curpath));
}

int			cd_switch_dir(char *operand, char *curpath,
	int pflag, t_sh *shell)
{
	if (cd_check_access(curpath, operand))
		return (1);
	if (chdir(curpath) == -1)
	{
		ft_dprintf(2, "42sh: cd: Unhandled exception\n");
		return (1);
	}
	return (change_envs(curpath, pflag, shell));
}

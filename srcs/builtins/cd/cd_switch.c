/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 21:35:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 15:59:48 by wbraeckm         ###   ########.fr       */
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

	if (get_env(shell, "PWD", &old_pwd) == SH_SUCCESS)
		repl_env(shell, "OLDPWD", old_pwd);
	if (pflag)
		getcwd(curpath, MAXPATHLEN * 2 + 1);
	repl_env(shell, "PWD", curpath);
	return (0);
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

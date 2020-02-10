/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:43:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/10 14:49:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtin.h"
#include <sys/param.h>

extern int	g_optind;
extern int	g_optopt;

/*
** NOTE: do we really need another buffer?
*/

static void	dot_dot_sanitization(char *curpath)
{
	char	buffer[MAXPATHLEN * 2 + 1];
	char	*tok;
	char	*prev_tok;

	ft_strncpy(buffer, curpath, MAXPATHLEN * 2);
	tok = buffer;
	prev_tok = NULL;
	ft_memset(curpath, 0, MAXPATHLEN * 2 + 1);
	ft_strcat(curpath, "/");
	while ((tok = ft_strtok(tok, "/")) && is_dir(curpath))
	{
		if (!ft_strequ(tok, "..") && !ft_strequ(tok, "."))
		{
			if (ft_strlen(curpath) != 1)
				ft_strcat(curpath, "/");
			ft_strcat(curpath, tok);
		}
		else if (!ft_strequ(tok, "."))
			trim_last_dir(curpath);
		prev_tok = tok;
		tok = NULL;
	}
}

/*
** Step 8 of posix notes
** NOTE: Does not allocate another string, directly modifies the current one
*/

static int	sanitize_curpath(char *curpath)
{
	char	*error;
	size_t	len;

	while ((error = ft_strstr(curpath, "/./")))
		ft_memmove(error, error + 2, ft_strlen(error + 2) + 1);
	dot_dot_sanitization(curpath);
	while ((error = ft_strstr(curpath, "//")))
	{
		len = ft_strspn(error, "/");
		ft_memmove(error, error + len - 1, ft_strlen(error + len - 1) + 1);
	}
	return (0);
}

static int	get_curpath(char *path, t_sh *shell, char *curpath, int pflag)
{
	char	pwd[MAXPATHLEN * 2 + 1];

	pwd[0] = '\0';
	if (cd_get_pwd(shell, pwd, MAXPATHLEN * 2) == -1)
	{
		ft_dprintf(2, "42sh: cd: could not get pwd\n");
		return (-1);
	}
	if (path[0] == '/' ||
		ft_strstartswith(path, ".") || ft_strstartswith(path, "..") ||
		cd_scan_cdpath(shell, path, curpath) == -1)
		ft_strcpy(curpath, path);
	if (pflag)
		return (0);
	if (*curpath != '/')
	{
		if (pwd[0] && pwd[ft_strlen(pwd) - 1] != '/')
			ft_strlcat(pwd, "/", MAXPATHLEN * 2 + 1);
		ft_strlcat(pwd, curpath, MAXPATHLEN * 2 + 1);
		ft_strncpy(curpath, pwd, MAXPATHLEN * 2);
	}
	return (sanitize_curpath(curpath));
}

static int	get_start_operand(int argc, char **argv,
	t_sh *shell, char **operand)
{
	if (argc == 0)
	{
		if (get_var(shell, "HOME", operand) != SH_SUCCESS)
		{
			ft_dprintf(2, "42sh: cd: HOME not set\n");
			return (1);
		}
	}
	else if (ft_strequ(argv[0], "-"))
	{
		if (get_var(shell, "OLDPWD", operand) != SH_SUCCESS)
		{
			ft_dprintf(2, "42sh: cd: OLDPWD not set\n");
			return (1);
		}
	}
	else
		*operand = argv[0];
	if (ft_strlen(*operand) > MAXPATHLEN * 2)
	{
		ft_dprintf(2, "42sh: cd: operand too long\n");
		return (1);
	}
	return (0);
}

int			cd_builtin(int argc, char **argv, t_sh *shell)
{
	int		ret;
	int		pflag;
	char	curpath[MAXPATHLEN * 2 + 1];
	char	*operand;

	pflag = 0;
	ft_bzero(curpath, sizeof(curpath));
	while ((ret = ft_getopt(argc, argv, "LP")) != -1)
	{
		if (ret == 'L' || ret == 'P')
			pflag = (ret == 'P');
		else if (ret == '?')
			return (ft_dprintf(2, "42sh: cd: -%c: invalid option\n"
				"cd: usage: cd [-L|-P] [dir]\n", g_optopt) > 0);
	}
	argc -= g_optind;
	argv += g_optind;
	if (get_start_operand(argc, argv, shell, &operand) ||
		(ret = get_curpath(operand, shell, curpath, pflag)) == -1 ||
		cd_switch_dir(operand, curpath, pflag, shell))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:39:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 16:14:47 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtin.h"
#include <sys/stat.h>
#include <sys/param.h>

int		ft_is_dir(char *str)
{
	struct stat st;

	if (stat(str, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int		cd_get_pwd(t_sh *shell, char *buffer, size_t buff_size)
{
	char	*value;

	if (get_env(shell, "PWD", &value) != SH_SUCCESS)
	{
		ft_strlcat(buffer, value, buff_size + 1);
		return (0);
	}
	if (!getcwd(buffer, buff_size))
		return (-1);
	return (0);
}

char	*trim_last_dir(char *path)
{
	char	*last;

	if (!(last = ft_strrchr(path, '/')))
		return (path);
	if (last != path)
		*last = '\0';
	else
		*(last + 1) = '\0';
	return (path);
}

int		cd_scan_cdpath(t_sh *shell, char *path, char *curpath)
{
	char		buffer[MAXPATHLEN + 1];
	char		*cdpath;
	char		**split;
	size_t		i;

	if (get_env(shell, "CDPATH", &cdpath) != SH_SUCCESS ||
		!(split = ft_strsplit(cdpath, ':')))
		return (-1);
	i = 0;
	while (split[i])
	{
		ft_strcpy(buffer, split[i]);
		if (buffer[ft_strlen(buffer) - 1] != '/')
			ft_strcat(buffer, "/");
		ft_strcat(buffer, path);
		if (ft_is_dir(buffer))
		{
			ft_freesplit(split);
			ft_strcpy(curpath, buffer);
			return (0);
		}
		i++;
	}
	ft_freesplit(split);
	return (-1);
}

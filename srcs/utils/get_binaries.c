/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:27:00 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 16:27:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_binaries(t_sh *shell, char **paths, char ***binaries)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			i;
	size_t			j;

	(void)shell;
	i = 0;
	while (paths[i])
	{
		j = 0;
		if (!(dirp = opendir(paths[i])))
			return (SH_ERR_OPEN_DIR);
		while ((dp = readdir(dirp)))
			*binaries[j++] = dp->d_name;
		i++;
		closedir(dirp);
	}
	return (SH_SUCCESS);
}

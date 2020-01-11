/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:42:42 by ntom              #+#    #+#             */
/*   Updated: 2020/01/11 14:29:28 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh.h"

int		is_directory(const char *path)
{
	struct stat	path_stat;

	return ((stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)));
}

int		replace_logname(t_sh *shell, char **str)
{
	char		*tmp;
	char		*tofree;
	int			ret;
	int			i;

	if ((ret = get_env_clone(shell, "HOME", &tmp) > 0))
		return (ret);
	i = ft_strlen(tmp) - 1;
	tofree = *str;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '/')
		{
			while (tmp[++i])
				tmp[i] = '\0';
			if (!(*str = ft_strjoin(tmp, (*str + 1))))
				return (SH_ERR_MALLOC);
			free(tmp);
			free(tofree);
			(*str)[ft_strlen(*str) - 1] = '\0';
			if (!is_directory(*str))
			{
				dprintf(2, "sh: no such user or named directory: %s\n", *str);
				return (SH_ERR_NOEXIST);
			}
			return (SH_SUCCESS);
		}
		--i;
	}
	return (SH_ERR_ENV_NOEXIST);
}

int		replace_home(t_sh *shell, char **str)
{
	char		*tmp;
	char		*tofree;
	int			ret;

	tofree = *str;
	if ((ret = get_env(shell, "HOME", &tmp) > 0))
		return (ret);
	if (!(*str = ft_strjoin(tmp, (*str + 1))))
		return (SH_ERR_MALLOC);
	free(tofree);
	return (SH_SUCCESS);
}

int		replace_tilde(t_sh *shell, char *str, char **result)
{
	(void)result;
	if (str[0] != '~')
		return (SH_SUCCESS);
	else if (str[1] == '\n' || str[1] == '\0' || str[1] == '/')
		return (replace_home(shell, &str));
	else
		return (replace_logname(shell, &str));
	return (SH_SUCCESS);
}

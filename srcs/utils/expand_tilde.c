/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:42:42 by ntom              #+#    #+#             */
/*   Updated: 2020/01/12 18:09:41 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh.h"

int		is_directory(const char *path)
{
	struct stat	path_stat;

	return ((stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)));
}

int		expand_logname(t_sh *shell, char *str, char **result)
{
	char		*tmp;
	int			ret;
	int			i;

	if ((ret = get_env_clone(shell, "HOME", &tmp) > 0))
		return (ret);
	i = ft_strlen(tmp) - 1;
	while (i >= 0 && tmp)
	{
		if (tmp[i] == '/')
		{
			while (tmp[++i])
				tmp[i] = '\0';
			if (!(*result = ft_strjoin(tmp, (str + 1))))
				return (SH_ERR_MALLOC);
			//(*result)[ft_strlen(*result) - 1] = '\0';//remove newline
			return (SH_SUCCESS);
		}
		--i;
	}
	return (SH_ERR_ENV_NOEXIST);
}

int		expand_home(t_sh *shell, char *str, char **result)
{
	char		*tmp;
	int			ret;

	if ((ret = get_env(shell, "HOME", &tmp) > 0))
		return (ret);
	if (!(*result = ft_strjoin(tmp, (str + 1))))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		expand_tilde(t_sh *shell, char *str, char **result)
{
	*result = ft_strdup(str);
	if (!str || str[0] != '~' || ft_strchr(str, '\\') || ft_strchr(str, '\"'))
		return (SH_SUCCESS);
	else if (str[1] == '\n' || str[1] == '\0' || str[1] == '/')
		return (expand_home(shell, str, result));
	else
		return (expand_logname(shell, str, result));
	return (SH_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:42:42 by ntom              #+#    #+#             */
/*   Updated: 2020/01/10 17:30:06 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh.h"

static int	replace_logname(t_sh *shell, char **str)
{
	char	**tmp;
	int		ret;
	int		i;

	tmp = NULL;
	if ((ret = get_env(shell, "HOME", tmp) > 0))
		return (ret);
	i = ft_strlen(*tmp) - 1;
	while (tmp && *tmp[i])
	{
		if (*tmp[i] == '/')
		{
			while (*tmp[++i])
				*tmp[i] = '\0';
			*str = ft_strjoin(*tmp, (*str + 1));
			return (SH_SUCCESS);
		}
		--i;
	}
	return (SH_ERR_ENV_NOEXIST);
}

static int	replace_home(t_sh *shell, char **str)
{
	char	**tmp;
	int		ret;

	tmp = NULL;
	if ((ret = get_env(shell, "HOME", tmp) > 0))
		return (ret);
	*str = ft_strjoin(*tmp, (*str + 1));
	return (SH_SUCCESS);
}

int			replace_tilde(t_sh *shell, char **str)
{
	if (*str[0] != '~')
		return (SH_SUCCESS);
	else if (*str[1] == '\0' || *str[1] == '/')
		return (replace_home(shell, str));
	else
		return (replace_logname(shell, str));
	return (SH_SUCCESS);
}

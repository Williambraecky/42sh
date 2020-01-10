/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:42:42 by ntom              #+#    #+#             */
/*   Updated: 2020/01/10 16:59:32 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh.h"

static int	replace_logname(t_sh *shell, char **str)
{
	char	*tmp;
	int		ret;
	char	*tmp1;

	if ((ret = get_env(shell, "HOME", &tmp) > 0))
		return (ret);
	tmp = ft_strdup(tmp);
	tmp1 = ft_strrchr(tmp, '/');
	if (tmp1)
		ft_strcpy(tmp1, (*str + 1));
	free(tmp);
	return (SH_SUCCESS);
}

static int	replace_home(t_sh *shell, char **str)
{
	char	*tmp;
	int		ret;

	if ((ret = get_env(shell, "HOME", &tmp) > 0))
		return (ret);
	tmp = ft_strdup(tmp);
	ft_strcpy(tmp, (*str + 1));
	free(tmp);
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

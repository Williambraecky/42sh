/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aliases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:43:57 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/10 17:34:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*g_base_alias[][2] =
{
	{"ls", "ls -G"},
	{NULL, NULL},
};

int			init_aliases(t_sh *shell)
{
	size_t	i;
	int		ret;

	ret = 0;
	i = 0;
	while (g_base_alias[i][0] != NULL && ret == SH_SUCCESS)
	{
		ret = add_alias(shell, g_base_alias[i][0], g_base_alias[i][1]);
		i++;
	}
	return (ret);
}

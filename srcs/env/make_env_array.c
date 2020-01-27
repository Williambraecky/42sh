/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:30:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:36:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		make_env_array(t_sh *shell, char ***array)
{
	t_map	*vars;
	t_var	*var;
	size_t	i;
	size_t	j;

	vars = shell->vars;
	if (!(*array = ft_memalloc(sizeof(**array) * (count_env(shell) + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	j = 0;
	while (i < vars->max_size)
	{
		if (vars->nodes[i].is_used)
		{
			var = vars->nodes[i].value;
			if (var->exported && !((*array)[j++] = ft_strformat("%s=%s",
				vars->nodes[i].key, var->var)))
			{
				ft_freesplit(*array);
				return (SH_ERR_MALLOC);
			}
		}
		i++;
	}
	return (SH_SUCCESS);
}

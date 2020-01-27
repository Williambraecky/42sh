/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 22:01:48 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:03:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t		count_env(t_sh *shell)
{
	size_t	i;
	size_t	count;
	t_var	*var;

	if (!shell->vars)
		return (0);
	i = shell->vars->max_size;
	count = 0;
	while (i--)
	{
		if (shell->vars->nodes[i].is_used)
		{
			var = (t_var*)shell->vars->nodes[i].value;
			if (var->exported)
				count++;
		}
	}
	return (count);
}

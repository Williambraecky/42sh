/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:21:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/10 18:00:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: replace or add to env
*/

int		repl_env(t_sh *shell, char *k, char *v)
{
	int		ret;
	t_var	*var;

	if (!has_var(shell, k))
		return (add_env(shell, k, v));
	if ((ret = repl_var(shell, k, v)))
		return (ret);
	var = ft_mapget(shell->vars, k);
	var->exported = 1;
	return (SH_SUCCESS);
}

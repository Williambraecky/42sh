/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:21:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:12:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: replace or add to env
*/

int		repl_env(t_sh *shell, char *k, char *v)
{
	if (!has_var(shell, k))
		return (add_env(shell, k, v));
	return (repl_var(shell, k, v));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:42:48 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:48:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			repl_var(t_sh *shell, char *key, char *value)
{
	char	*val_dup;
	t_var	*old;

	if (!shell->vars)
		return (SH_ERR_NOEXIST);
	if ((old = (t_var*)ft_mapget(shell->vars, key)))
	{
		if (!(val_dup = ft_strdup(value)))
			return (SH_ERR_MALLOC);
		free(old->var);
		old->var = val_dup;
		return (SH_SUCCESS);
	}
	return (add_var(shell, key, value));
}

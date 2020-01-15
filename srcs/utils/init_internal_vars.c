/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_internal_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:39:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 14:45:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		init_internal_vars(t_sh *shell)
{
	char	*tmp;
	int		ret;

	ret = 0;
	ret += add_internal(shell, "?", "0");
	if (!(tmp = ft_itoa(getpid())))
		return (1);
	ret += add_internal(shell, "$", tmp);
	free(tmp);
	ret += add_internal(shell, "PS1", "\\w> ");
	return (ret);
}

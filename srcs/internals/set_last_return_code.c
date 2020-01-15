/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_return_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:53:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 14:37:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		set_last_return_code(t_sh *shell, int ret)
{
	char	*str;
	int		ret_;

	if (get_last_return_code(shell) == ret)
		return (SH_SUCCESS);
	if (!(str = ft_itoa(ret)))
		return (SH_ERR_MALLOC);
	ret_ = repl_internal(shell, "?", str);
	free(str);
	return (ret_);
}

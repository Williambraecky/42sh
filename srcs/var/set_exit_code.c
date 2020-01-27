/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:50:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:51:27 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		set_exit_code(t_sh *shell, int ret)
{
	char	*str;
	int		ret_;

	if (shell->block_ret_update)
		return (SH_SUCCESS);
	if (get_exit_code(shell) == ret)
		return (SH_SUCCESS);
	if (!(str = ft_itoa(ret)))
		return (SH_ERR_MALLOC);
	ret_ = repl_var(shell, "?", str);
	free(str);
	return (ret_);
}

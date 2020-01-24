/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:40:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 03:14:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int			fc_builtin(int argc, char **argv, t_sh *shell)
{
	t_fc	fc;

	ft_bzero(&fc, sizeof(fc));
	if (willifc_read_opt(&fc, &argc, &argv))
		return (1);
	willifc_read_first_last(shell, &fc, argc, argv);
	if (fc.err)
		return (1);
	if (fc.opt_s)
		fc.err = willifc_handle_s(shell, &fc);
	else if (fc.opt_l)
		fc.err = willifc_handle_l(shell, &fc);
	else
		fc.err = willifc_handle_edit(shell, &fc);
	if (fc.opt_s || !fc.opt_l)
		shell->block_history = 1;
	return (fc.err);
}

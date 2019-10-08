/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:49:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 14:42:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: Main shell free procedure add fields to be freed here
*/

void	free_sh(t_sh *shell)
{
	ft_mapdel(shell->env);
	if (shell->prompt_mode)
		tcsetattr(SH_IN, TCSADRAIN, &shell->old_termios);
}

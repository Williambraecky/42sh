/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:27:50 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/24 18:39:03 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		remove_history(t_sh *shell, size_t index)
{
	if (index >= shell->history.size)
		return (SH_ERR_NOEXIST);
	return (ft_vecdel(&shell->history, index));
}

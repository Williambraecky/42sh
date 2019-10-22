/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:26:41 by ntom              #+#    #+#             */
/*   Updated: 2019/10/22 18:39:10 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_history(t_sh *shell, size_t index, char **histo)
{
	if (!(*histo = ft_vecget(&shell->history, index)))
		return (SH_ERR_NOEXIST);
	return (SH_SUCCESS);
}

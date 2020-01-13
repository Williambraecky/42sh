/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:37:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 17:40:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		cmd_new(t_cmd **cmd)
{
	if (!(*cmd = ft_memalloc(sizeof(**cmd))))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

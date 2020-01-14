/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:48:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 14:42:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: use real substitute function
*/

int	proxy_substitute(t_sh *shell, char *str, char **result)
{
	(void)shell;
	if (expand_param(shell, str, result) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (remove_quotes(*result, result));
}

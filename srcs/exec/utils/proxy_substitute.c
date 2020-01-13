/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:48:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 00:03:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: use real substitute function
*/

int	proxy_substitute(t_sh *shell, char *str, char **result)
{
	(void)shell;
	if (!(*result = ft_strdup(str)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

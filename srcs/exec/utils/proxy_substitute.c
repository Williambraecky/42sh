/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:48:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 23:34:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: use real substitute function
*/

int	proxy_substitute(t_sh *shell, char *str, char **result)
{
	(void)shell;
	return (remove_quotes(str, result));
}

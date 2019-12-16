/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:28:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 18:34:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: simply returns error code 1
*/

int		false_builtin(int argc, char **argv, t_sh *shell)
{
	(void)argc;
	(void)argv;
	(void)shell;
	return (1);
}

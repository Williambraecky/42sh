/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:24:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 18:38:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: simply prints pwd; should use from env but if it's not present getcwd
*/

int		pwd_builtin(int argc, char **argv, t_sh *shell)
{
	(void)argc;
	(void)argv;
	(void)shell;
	return (0);
}

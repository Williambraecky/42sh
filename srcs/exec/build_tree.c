/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:42:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 15:00:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** TODO: everything; this should build the current working tree
*/

/*
** NOTE: return error code ?
*/

t_cmd	*build_tree(t_sh *shell, t_lexer *lexer)
{
	t_build	build;

	ft_memset(&build, 0, sizeof(build));
	(void)shell;
	(void)lexer;
	return (NULL);
}

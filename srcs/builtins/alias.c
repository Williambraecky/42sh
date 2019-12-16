/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:01:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 17:44:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** TODO:
**  no args:
**   1: for every alias create a string in form key='value'
**   2: sort these string by ascii order
**   3: print them
**   4: ???
**   5: profit
**  with args, for every arg:
**   1: split first arg on = (no need to actually split just replace = with \0)
**   2: validate alias name (should be a-zA-Z0-9 probably)
**   3: tokenize string after = (/!\ lexer should not ask for prompt again)
**   4: add to alias (remove if it exists before)
**   5: ???
**   6: profit
*/

int		alias_builtin(int argc, char **argv, t_sh *shell)
{
	(void)argc;
	(void)argv;
	(void)shell;
	return (0); //TODO: return non-zero on error
}

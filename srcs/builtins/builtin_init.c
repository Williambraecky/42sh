/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:13:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 18:31:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: Main builtin initializing method
** TODO: add more builtins
** "test",
*/

t_bltin		g_builtin_table[] =
{
	{"cd", cd_builtin},
	{"alias", alias_builtin},
	{"type", type_builtin},
	{"set", set_builtin},
	{"unset", unset_builtin},
	{"echo", echo_builtin},
	{"export", export_builtin},
	{"hash", hash_builtin},
	{"rehash", rehash_builtin},
	{"pwd", pwd_builtin},
	{"fg", fg_builtin},
	{"bg", bg_builtin},
	{"jobs", jobs_builtin},
	{"true", true_builtin},
	{"false", false_builtin},
	{"history", history_builtin},
	{"", NULL}
};

size_t		g_table_size = sizeof(g_builtin_table) / sizeof(g_builtin_table[0]);

/*
** NOTE: incomplete
*/

int			builtin_init(t_sh *shell)
{
	size_t	i;

	(void)shell;
	i = 0;
	while (i < g_table_size)
	{
		i++;
	}
	return (SH_SUCCESS);
}

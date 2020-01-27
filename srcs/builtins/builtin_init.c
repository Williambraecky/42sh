/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:13:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:02:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: Main builtin initializing method
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
	{"setenv", export_builtin},
	{"hash", hash_builtin},
	{"rehash", rehash_builtin},
	{"pwd", pwd_builtin},
	{"fg", fg_builtin},
	{"bg", bg_builtin},
	{"jobs", jobs_builtin},
	{"true", true_builtin},
	{"false", false_builtin},
	{"history", history_builtin},
	{"test", test_builtin},
	{"exit", exit_builtin},
	{"unsetenv", unsetenv_builtin},
	{"unalias", unalias_builtin},
	{"fc", fc_builtin}
};

size_t		g_table_size = sizeof(g_builtin_table) / sizeof(g_builtin_table[0]);

int			builtin_init(t_sh *shell)
{
	size_t	i;

	i = 0;
	while (i < g_table_size)
	{
		if (ft_mapput(shell->builtins, g_builtin_table[i].name,
			&g_builtin_table[i], sizeof(*g_builtin_table)) != MAP_OK)
			return (SH_ERR_MALLOC);
		i++;
	}
	return (SH_SUCCESS);
}

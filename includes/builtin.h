/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:53 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/16 18:31:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "sys/types.h"
# include "sys/stat.h"
# include "unistd.h"
# include "sh.h"

/*
** Prototypes
*/

/*
** Builtins
*/

int			cd_builtin(int argc, char **argv, t_sh *shell);
int			alias_builtin(int argc, char **argv, t_sh *shell);
int			type_builtin(int argc, char **argv, t_sh *shell);
int			set_builtin(int argc, char **argv, t_sh *shell);
int			unset_builtin(int argc, char **argv, t_sh *shell);
int			echo_builtin(int argc, char **argv, t_sh *shell);
int			export_builtin(int argc, char **argv, t_sh *shell);
int			hash_builtin(int argc, char **argv, t_sh *shell);
int			rehash_builtin(int argc, char **argv, t_sh *shell);
int			pwd_builtin(int argc, char **argv, t_sh *shell);
int			fg_builtin(int argc, char **argv, t_sh *shell);
int			bg_builtin(int argc, char **argv, t_sh *shell);
int			jobs_builtin(int argc, char **argv, t_sh *shell);
int			true_builtin(int argc, char **argv, t_sh *shell);
int			false_builtin(int argc, char **argv, t_sh *shell);
int			history_builtin(int argc, char **artv, t_sh *shell);

/*
** Utils
*/

int			ft_is_dir(char *str);
char		*trim_last_dir(char *path);
int			cd_scan_cdpath(t_sh *shell, char *path, char *curpath);
int			cd_get_pwd(t_sh *shell, char *buffer, size_t buff_size);
int			cd_switch_dir(char *operand, char *curpath, int pflag, t_sh *shell);

#endif

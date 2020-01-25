/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:53 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/25 22:35:22 by wbraeckm         ###   ########.fr       */
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
** Typedefs
*/

typedef struct s_fc	t_fc;

/*
** Structures
*/

struct		s_fc
{
	int		opt_l;
	int		opt_n;
	int		opt_r;
	int		opt_e;
	char	*editor;
	int		opt_s;
	char	*s_replace;
	size_t	first;
	size_t	last;
	int		err;
};

/*
** Prototypes
*/

int			builtin_init(t_sh *shell);

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
int			test_builtin(int ac, char **av, t_sh *shell);
int			type_builtin(int ac, char **av, t_sh *shell);
int			exit_builtin(int argc, char **argv, t_sh *shell);
int			unsetenv_builtin(int argc, char **argv, t_sh *shell);
int			fc_builtin(int argc, char **argv, t_sh *shell);
int			unalias_builtin(int argc, char **argv, t_sh *shell);
int			fc_builtin(int argc, char **argv, t_sh *shell);

/*
** Utils
*/

/*
**   CD Utils
*/

int			ft_is_dir(char *str);
char		*trim_last_dir(char *path);
int			cd_scan_cdpath(t_sh *shell, char *path, char *curpath);
int			cd_get_pwd(t_sh *shell, char *buffer, size_t buff_size);
int			cd_switch_dir(char *operand, char *curpath, int pflag, t_sh *shell);

/*
**   Test Utils
*/

int			int_cmp(char *s1, char *s2, char *cmp_op);
int			not_op_reverse(int ret, int not_op);
int			cmp_op(char **av, int ac, int not_op);
int			test_op(char op, char **av, int ac, int not_op);

/*
**   Fc Utils
*/

int			fc_handle_l(t_sh *shell, t_fc *fc);
size_t		*fc_make_range(size_t first, size_t last);
int			fc_read_opt(t_fc *fc, int *argc, char ***argv);
void		fc_read_first_last(t_sh *shell, t_fc *fc,
	int argc, char **argv);
int			fc_ensure_newline(char **command);
int			fc_handle_s(t_sh *shell, t_fc *fc);
char		*fc_get_filename(void);
char		*file_to_str(int fd);
int			fc_handle_edit(t_sh *shell, t_fc *fc);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/29 17:04:39 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*
** Includes
*/

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <dirent.h>

/*
** Defines
*/

# define SH_IN 0
# define SH_OUT 1
# define SH_ERR 2
# define INTERACTIVE 0
# define NON_INTERACTIVE 1
# define SH_SUCCESS 0
# define SH_ERR_NOEXIST 1
# define SH_ERR_MALLOC 2
# define SH_ERR_ENV_NOEXIST 3
# define SH_OPEN_HIST_FAIL 4
# define SH_OPEN_DIR_FAIL 5
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/*
** Typedefs
*/

typedef struct s_sh	t_sh;
typedef struct stat	t_stat;
typedef struct termios	t_termi;
typedef struct winsize	t_winsiz;

/*
** Structures
*/

struct		s_sh
{
	t_map	*env;
	t_vec	history;
	int		prompt_mode;
	t_termi	old_termios;
	t_termi	current_termios;
	pid_t	pid;
};

/*
** Prototypes
*/

/*
**  Env
*/

int			add_env(t_sh *shell, char *key, char *value);
int			copy_env(t_sh *shell, const char **env);
int			get_env_clone(t_sh *shell, char *key, char **result);
int			get_env(t_sh *shell, char *key, char **result);
int			has_env(t_sh *shell, char *key);
int			repl_env(t_sh *shell, char *key, char *value);

/*
** History
*/

int			init_history(t_sh *shell);
int			get_history(t_sh *shell, size_t index, char **histo);

/*
**  Utils
*/

void		free_sh(t_sh *shell);
int			init_interactive_mode(t_sh *shell);
void		ignore_signal(int signo);
int			is_char_escaped(char *str, int index);
int			get_cursor_pos(t_sh *sh, int *x, int *y);
char		*getpwd(t_sh *shell);
char		*getpwd_short(t_sh *shell);
int			gettermsize(t_winsiz *winsize);
size_t		strlen_nocolor(char *str);
void		window_change_signal(int signo);
int			get_paths(t_sh *shell, char ***paths);
int			get_binaries(t_sh *shell, char **paths, char ***binaries);
void		*bell_retnull(void);


#endif

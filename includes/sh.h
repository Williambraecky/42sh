/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/17 20:38:29 by wbraeckm         ###   ########.fr       */
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
# define SH_ERR_SYNTAX 4
# define SH_ERR_OPEN_HIST 5
# define SH_ERR_OPEN_DIR 6
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
# ifndef USE_BELL
#  define USE_BELL 1
# endif

/*
** Typedefs
*/

typedef enum e_intern	t_intyp;
typedef enum e_extype	t_extype;
typedef union u_intval	t_intvl;
typedef struct s_alias	t_alias;
typedef struct s_bltin	t_bltin;
typedef struct s_sh	t_sh;
typedef struct stat	t_stat;
typedef struct termios	t_termi;
typedef struct winsize	t_winsiz;

/*
** Enums
*/

enum	e_intern
{
	UNDEFINED,
	STRING,
	FLOAT,
	DOUBLE,
	INTEGER,
	LONG
};

enum	e_extype
{
	BUILTIN,
	EXECUTABLE
};

/*
** Structures
*/

/*
** TODO: maybe use them? unsure if we actually need such thing
*/

union		u_intval
{
	char	*str_;
	float	flt_;
	double	dbl_;
	int		int_;
	long	lng_;
};

struct		s_intern
{
	t_intyp	type;
	t_intvl	val;
};

struct		s_alias
{
	char	*str;
	t_vec	*tokens;
};

struct		s_bltin
{
	char	*name;
	int		(*fnc_ptr)(int, char**, t_sh*);
};

/*
** NOTE:
**  - internals => map<string->string>
**  - env => map<string->string>
**  - aliases -> map<string->t_alias>
**	- builtins -> map<stirng->t_bltin>
**  - history -> vec<string>
**  - prompt_mode -> either INTERACTIVE or NON_INTERACTIVE
*/

struct		s_sh
{
	t_map	*internals;
	t_map	*env;
	t_map	*aliases;
	t_map	*builtins;
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
** Alias
*/

int			add_alias(t_sh *shell, char *alias, t_vec *tokens);
int			has_alias(t_sh *shell, char *alias);
int			remove_alias(t_sh *shell, char *alias);
int			resolve_alias(t_sh *shell, char *alias, t_vec **tokens);
t_alias		*get_alias(t_sh *shell, char *alias);

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
void		*ring_bell(void);

#endif

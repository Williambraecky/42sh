/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 01:23:01 by wbraeckm         ###   ########.fr       */
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
# include <sys/stat.h>
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
# define SH_ERR_PIPE 7
# define SH_ERR_DUP 8
# define SH_ERR_SIGINT 9
# define SH_ERR_FORK 10
# define SH_ERR_OPEN 11
# define SH_ERR_KILL 12
# define SH_ERR_BAD_SUBST 13
# define SH_ERR_READ 14
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
# ifndef USE_BELL
#  define USE_BELL 1
# endif
# define FIRST_CHAR 0
# define SUBST_WORD 0
# define SUBST_PARAM 1
# define ASSIGN_WORD 2
# define SUBST_NULL 3
# define ERROR_EXIT 4
# define REMOVE_SUFFIX 5
# define REMOVE_PREFIX 6
# define DO_NOTHING 7
# define PBUFF_DEF_SIZE 512
# define SUB_QUOTE (1 << 0)
# define SUB_PARAM (1 << 1)
# define SUB_TILDE (1 << 2)
# define SUB_ASSIGN (1 << 3)

/*
** Typedefs
*/

typedef enum e_intern	t_intyp;
typedef enum e_extype	t_extype;
typedef union u_intval	t_intvl;
typedef struct s_bltin	t_bltin;
typedef struct s_hashed	t_hashed;
typedef struct s_buff	t_buff;
typedef struct s_sh	t_sh;
typedef struct stat	t_stat;
typedef struct termios	t_termi;
typedef struct winsize	t_winsiz;
typedef struct s_subst	t_subst;
typedef struct s_bparam	t_bparam;

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

struct		s_bltin
{
	char	*name;
	int		(*fnc_ptr)(int, char**, t_sh*);
};

struct		s_hashed
{
	int		uses;
	char	*path;
};

struct			s_buff
{
	char		*buffer;
	size_t		max_size;
	size_t		size;
};

/*
** NOTE:
**  - internals => map<string->string>
**  - env => map<string->string>
**  - aliases -> map<string->string>
**  - builtins -> map<string->t_bltin>
**  - use_hash -> map<string->t_hashed>
**  - history -> vec<string>
**  - prompt_mode -> either INTERACTIVE or NON_INTERACTIVE
*/

/*
** NOTE: for fd_backups should we not allow to close them or
**    create another backup before
*/

struct		s_sh
{
	t_map	*internals;
	t_map	*env;
	t_map	*aliases;
	t_map	*builtins;
	t_map	*use_hash;
	t_vec	history;
	t_vec	jobs;
	int		prompt_mode;
	t_termi	old_termios;
	t_termi	current_termios;
	pid_t	pid;
	int		running;
	int		stop_code;
};

struct		s_subst
{
	t_sh	*shell;
	t_buff	buffer;
	t_vec	stack;
	char	*str;
	size_t	i;
	int		profile;
	int		err;
};

struct		s_bparam
{
	char	*param;
	char	*key;
	char	*val;
	int		unset;
	size_t	end;
	int		hashtag;
	char	*word;
	int		colon;
	int		operator;
	char	*result;
};

/*
** Prototypes
*/

/*
** Alias
*/

int			add_alias(t_sh *shell, char *alias, char *aliased);
int			has_alias(t_sh *shell, char *alias);
int			remove_alias(t_sh *shell, char *alias);
char		*get_alias(t_sh *shell, char *alias);
int			repl_alias(t_sh *shell, char *key, char *value);

/*
** Buffer
*/

int			buff_ninsert(t_buff *buffer, char *insert, size_t pos, size_t n);
int			buff_insert(t_buff *buffer, char *insert, size_t pos);
int			buff_remove(t_buff *buffer, size_t pos);
void		buff_clear(t_buff *buffer);
int			buff_nappend(t_buff *buffer, char *str, size_t n);
int			buff_append(t_buff *buffer, char *str);
int			buff_init(t_buff *buffer);
int			buff_init_size(t_buff *buffer, size_t size);

/*
**  Env
*/

int			add_env(t_sh *shell, char *key, char *value);
int			copy_env(t_sh *shell, const char **env);
int			get_env_clone(t_sh *shell, char *key, char **result);
int			get_env(t_sh *shell, char *key, char **result);
int			has_env(t_sh *shell, char *key);
void		remove_env(t_sh *shell, char *key);
int			repl_env(t_sh *shell, char *key, char *value);
int			make_env_array(t_sh *shell, char ***array);
int			make_env_array_no_malloc(t_sh *shell, char **array);

/*
** Internals
*/

int			add_internal(t_sh *shell, char *key, char *value);
int			get_internal_clone(t_sh *shell, char *key, char **result);
int			get_internal(t_sh *shell, char *key, char **result);
int			has_internal(t_sh *shell, char *key);
void		remove_internal(t_sh *shell, char *key);
int			repl_internal(t_sh *shell, char *key, char *value);
int			get_last_return_code(t_sh *shell);
int			set_last_return_code(t_sh *shell, int ret);

/*
** Hash
*/

int			get_hash(t_sh *shell, char *bin, t_hashed **hash);
int			has_hash(t_sh *shell, char *bin);
void		remove_hash(t_sh *shell, char *bin);
int			get_hash_ignorecase(t_sh *shell, char *str, char **result);
void		path_change(t_sh *shell);

/*
** History
*/

int			init_history(t_sh *shell);
int			get_history(t_sh *shell, size_t index, char **histo);
int			remove_history(t_sh *shell, size_t index);
int			add_history(t_sh *shell, char *str);

/*
** Substitute
*/

void		free_subst(t_subst *subst);
int			tilde_check(t_subst *subst, size_t j);
void		subst_handle_specials(t_subst *subst);
int			substitute(t_sh *shell, char *str, char **result, int profile);
void		substitute_tilde(t_subst *subst);
void		substitute_param(t_subst *subst);
void		substitute_parambrace(t_subst *subst);
int			is_valid_operator(char c);
void		read_operator(t_subst *subst, t_bparam *bparam);
void		apply_bparam_operator(t_subst *subst, t_bparam *bparam);
void		free_bparam(t_bparam *bparam);
void		apply_percent(t_subst *subst, t_bparam *bparam);
void		apply_hashtag(t_subst *subst, t_bparam *bparam);
void		apply_hashtag_flag(t_subst *subst, t_bparam *bparam);

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
int			resolve_path(t_sh *shell, char *name, char **result);
int			resolve_path_env(char *paths, char *name, char **result);
int			str_is_name(char *str);
int			backup_fds(t_sh *shell);
int			backup_fd(t_sh *shell, int fd);
int			map_del_filter(t_node *node);
int			expand_exclamation(t_sh *shell, char *str, char **result);
int			is_builtin(t_sh *shell, char *str);
int			gen_prompt_string(t_sh *shell, char *ps1, char **result);
int			end_gen_prompt(int ret, char **result, char *prompt);
int			is_valid_esc(char *prompt, size_t *i);
int			init_internal_vars(t_sh *shell);
int			vecgetlastmatch_index(t_vec *vec, char *find);
char		*get_signal_str(int status);
int			run_command(t_sh *shell, char *command);

#endif

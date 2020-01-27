/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:02:19 by ntom              #+#    #+#             */
/*   Updated: 2020/01/27 23:13:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** Includes
*/

# include "sh.h"

/*
** Defines
*/

# define PROC_FD_BACKUP_SIZE 10

/*
** Enums
*/

enum		e_type
{
	T_NEWLINE,
	T_BRACEPARAM,
	T_CMDSUBST,
	T_DOUBLE_AMPERSAND,
	T_DOUBLE_PIPE,
	T_DOUBLE_LESSER,
	T_DOUBLE_GREATER,
	T_LESSER_AND,
	T_GREATER_AND,
	T_IO_NUMBER,
	T_LESSER,
	T_GREATER,
	T_PIPE,
	T_QUOTE,
	T_DOUBLE_QUOTE,
	T_SEMICOLON,
	T_AMPERSAND,
	T_WSPACE,
	T_WORD,
	T_NULL
};

enum		e_tmask
{
	M_NEWLINE = 1 << T_NEWLINE,
	M_BRACEPARAM = 1 << T_BRACEPARAM,
	M_CMDSUBST = 1 << T_CMDSUBST,
	M_DOUBLE_AMPERSAND = 1 << T_DOUBLE_AMPERSAND,
	M_DOUBLE_PIPE = 1 << T_DOUBLE_PIPE,
	M_DOUBLE_LESSER = 1 << T_DOUBLE_LESSER,
	M_DOUBLE_GREATER = 1 << T_DOUBLE_GREATER,
	M_LESSER_AND = 1 << T_LESSER_AND,
	M_GREATER_AND = 1 << T_GREATER_AND,
	M_IO_NUMBER = 1 << T_IO_NUMBER,
	M_LESSER = 1 << T_LESSER,
	M_GREATER = 1 << T_GREATER,
	M_PIPE = 1 << T_PIPE,
	M_QUOTE = 1 << T_QUOTE,
	M_DOUBLE_QUOTE = 1 << T_DOUBLE_QUOTE,
	M_SEMICOLON = 1 << T_SEMICOLON,
	M_AMPERSAND = 1 << T_AMPERSAND,
	M_WSPACE = 1 << T_WSPACE,
	M_WORD = 1 << T_WORD,
	M_NULL = 1 << T_NULL,
	M_ANY = ~0
};

/*
** Typedefs
*/

typedef struct s_io		t_io;
typedef struct s_redir	t_redir;
typedef struct s_proc	t_proc;
typedef struct s_cmd	t_cmd;
typedef struct s_build	t_build;
typedef struct s_token	t_token;
typedef struct s_hdoc	t_hdoc;
typedef struct s_io_nb	t_io_nb;
typedef struct s_lexer	t_lexer;
typedef struct s_tdef	t_tdef;
typedef enum e_type		t_type;
typedef enum e_tmask	t_tmask;

/*
** Structures
*/

struct		s_io
{
	int		in;
	int		out;
	int		pipe_close;
};

struct		s_redir
{
	t_io_nb	*io_nb;
	t_token	*token;
	char	*filename;
	int		to;
};

/*
** NOTE: this should store related redirections etc
** NOTE: io used for pipes
** NOTE: fd_backups is for restoring fds after redirection
** NOTE: implementation only asks to handle 0 to 9 inclusive
*/

struct		s_proc
{
	t_cmd	*parent;
	t_proc	*next;
	char	*proc_str;
	pid_t	pid;
	t_vec	unprocessed_argv;
	char	*path;
	char	**argv;
	char	**env;
	t_map	*env_backup;
	t_map	*hash_backup;
	t_vec	redirections;
	t_vec	assignments;
	t_io	io;
	int		fd_backups[PROC_FD_BACKUP_SIZE];
	int		status;
	char	*status_str;
	int		stopped;
	int		completed;
	int		block_sigtstp;
};

/*
** NOTE: pipeline represented by [] t_proc represented by ()
**    t_lexer represented by {}
** {[(foo bar) | (baz)]; [(far bor)] && [(boz)]}
*/

struct		s_cmd
{
	t_proc	*pipeline;
	char	*cmd_str;
	int		status;
	pid_t	pgid;
	t_termi	termios;
	int		(*condition)(int);
	int		background;
	int		notified;
	t_cmd	*next;
};

struct		s_build
{
	t_cmd	*head;
	t_cmd	*work;
	t_proc	*work_proc;
	t_type	prev_type;
	int		expected_type;
};

/*
** NOTE: size = size of real struct; used for inheritance
*/

struct		s_token
{
	size_t	size;
	t_type	type;
	char	*str;
	size_t	len;
};

struct		s_hdoc
{
	t_token	token;
	char	*name;
	char	*content;
	int		pipe[2];
	int		completed;
};

struct		s_io_nb
{
	t_token	token;
	int		io_nb;
};

/*
** NOTE: clean_line is an unprocessed version of the line (used for history)
*/

struct		s_lexer
{
	t_vec	tokens;
	int		block_sigtstp;
	char	**alias_stack;
	int		can_be_alias;
	char	*clean_line;
	char	*line;
	size_t	line_size;
	size_t	i;
	t_vec	stack;
	t_build	build;
};

struct		s_tdef
{
	t_type	type;
	int		(*is_tok)(t_lexer *, t_token *);
	int		(*transform)(t_lexer *, t_token *);
};

/*
** Tokenization
*/

int			lexer(char *line, t_lexer *lex, t_sh *shell);
int			init_lexer(t_sh *shell, t_lexer *lexer, char *line);
int			tokenization(t_lexer *lexer, t_sh *shell);
void		token_free(t_token *token);
int			token_process(t_lexer *lexer, t_token *token);

/*
** Delimit
*/

int			delimit_token(t_lexer *lex, char **result);

/*
** Utils
*/

void		lexer_free(t_lexer *lexer);
int			stack_push(t_vec *stack, t_type type);
t_type		stack_pop(t_vec *stack);
t_type		stack_top(t_vec *stack);
int			stack_push_or_pop(t_vec *stack, t_type type);
int			is_escaped(t_vec *stack, char *str, size_t len);
int			delim_handle_specials(t_vec *stack, char *line, size_t len);
int			new_line_check(t_lexer *lex, size_t len);
int			make_stack_prompt(t_vec *stack, char **result);
int			lexer_handle_alias(t_sh *shell, t_lexer *lexer, char *str);
int			alias_stack_contains(t_lexer *lexer, char *str);
void		alias_stack_clear(t_lexer *lexer);
int			cmd_make_string(t_cmd *cmd);
int			proc_make_string(t_proc *proc);
int			match_special_character(char *str);
int			delim_stack_sig_top(t_vec *stack);
char		*get_signal_str(t_proc *proc);

/*
** Tokens
*/

int			istok_ampersand(t_lexer *lexer, t_token *token);
int			transform_ampersand(t_lexer *lexer, t_token *token);
int			istok_double_ampersand(t_lexer *lexer, t_token *token);
int			transform_double_ampersand(t_lexer *lexer, t_token *token);
int			istok_double_pipe(t_lexer *lexer, t_token *token);
int			transform_double_pipe(t_lexer *lexer, t_token *token);
int			istok_greater(t_lexer *lexer, t_token *token);
int			transform_greater(t_lexer *lexer, t_token *token);
int			istok_greaterand(t_lexer *lexer, t_token *token);
int			transform_greaterand(t_lexer *lexer, t_token *token);
int			istok_io_number(t_lexer *lexer, t_token *token);
int			transform_io_number(t_lexer *lexer, t_token *token);
int			istok_lesser(t_lexer *lexer, t_token *token);
int			transform_lesser(t_lexer *lexer, t_token *token);
int			istok_lesserand(t_lexer *lexer, t_token *token);
int			istok_pipe(t_lexer *lexer, t_token *token);
int			transform_pipe(t_lexer *lexer, t_token *token);
int			transform_lesserand(t_lexer *lexer, t_token *token);
int			istok_semicolon(t_lexer *lexer, t_token *token);
int			transform_semicolon(t_lexer *lexer, t_token *token);
int			istok_newline(t_lexer *lexer, t_token *token);
int			transform_newline(t_lexer *lexer, t_token *token);
int			istok_double_greater(t_lexer *lexer, t_token *token);
int			transform_double_greater(t_lexer *lexer, t_token *token);
int			istok_double_lesser(t_lexer *lexer, t_token *token);
int			transform_double_lesser(t_lexer *lexer, t_token *token);
int			istok_word(t_lexer *lexer, t_token *token);
int			transform_word(t_lexer *lexer, t_token *token);
int			istok_null(t_lexer *lexer, t_token *token);
int			transform_null(t_lexer *lexer, t_token *token);

/*
** Exec tree
*/

int			build_tree_apply_token(t_lexer *lexer, t_token *token);
int			init_build_tree(t_build *build);
int			exec_tree(t_sh *shell, t_cmd *tree);
int			exec_cmd(t_sh *shell, t_cmd *cmd);
int			exec_proc(t_sh *shell, t_proc *proc);
int			proc_exec_cmd(t_sh *shell, t_proc *proc);
int			prepare_proc(t_sh *shell, t_proc *proc);
int			prepare_hdoc(t_sh *shell, t_hdoc *doc);

int			apply_newline(t_token *token, t_build *build, t_lexer *lex);
int			apply_ampersand(t_token *token, t_build *build, t_lexer *lex);
int			apply_dampersand(t_token *token, t_build *build, t_lexer *lex);
int			apply_dampersand(t_token *token, t_build *build, t_lexer *lex);
int			apply_dpipe(t_token *token, t_build *build, t_lexer *lex);
int			apply_pipe(t_token *token, t_build *build, t_lexer *lex);
int			apply_word(t_token *token, t_build *build, t_lexer *lex);
int			apply_io_nb(t_token *token, t_build *build, t_lexer *lex);
int			apply_redir(t_token *token, t_build *build, t_lexer *lex);

/*
** Jobs
*/

int			jobs_add(t_sh *shell, t_cmd *cmd, int notify);
int			job_is_stopped(t_cmd *cmd);
int			job_is_completed(t_cmd *cmd);
void		job_wait(t_sh *shell, t_cmd *cmd);
int			jobs_to_background(t_sh *shell, t_cmd *cmd, int wake);
int			jobs_to_foreground(t_sh *shell, t_cmd *cmd, int wake);
void		jobs_update_status(t_sh *shell);
void		job_notify(t_sh *shell);
void		job_notify_cmd(t_cmd *cmd, size_t index, size_t max);
int			jobs_last_status(t_cmd *cmd);
void		job_continue(t_sh *shell, t_cmd *cmd, int fg);
t_cmd		*job_by_id(t_sh *shell, char *id);
void		print_lflag(t_cmd *cmd, size_t index, size_t max);
void		print_pflag(t_cmd *cmd, size_t index, size_t max);
void		basic_print(t_cmd *cmd, size_t index, size_t max);

/*
** Utils
*/

int			cmd_new(t_cmd **cmd);
int			proc_new(t_proc **proc);
int			or_condition(int last_ret_code);
int			and_condition(int last_ret_code);
void		free_tree(t_cmd *cmd);
void		free_cmd(t_cmd *cmd);
void		free_proc(t_proc *proc);
int			proc_is_empty(t_proc *proc);
int			cmd_is_empty(t_cmd *cmd);
int			proc_apply_redir(t_proc *proc);
int			redir_open_file(t_redir *redir);
int			redir_get_from(t_redir *redir);
int			redir_add_undo(t_proc *proc, int fd);
int			apply_base_redir(t_proc *proc, t_redir *redir);
int			apply_and_redir(t_proc *proc, t_redir *redir);
int			apply_dlesser_redir(t_proc *proc, t_redir *redir);
int			init_build_tree(t_build *build);

#endif

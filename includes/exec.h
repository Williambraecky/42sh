/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:45:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/08 16:02:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "sh.h"
# include "lexer.h"

/*
** Defines
*/

/*
** Typedefs
*/

typedef struct s_redir	t_redir;
typedef struct s_proc	t_proc;
typedef struct s_cmd	t_cmd;
typedef struct s_build	t_build;

/*
** Structures
*/

struct		s_redir
{
	t_io_nb	*io_nb;
	t_token	*token;
	char	*filename;
};

/*
** NOTE: this should store related redirections etc
*/

struct		s_proc
{
	t_cmd	*parent;
	t_proc	*next;
	pid_t	pid;
	int		argc;
	t_vec	unprocessed_argv; //NOTE: those are all T_WORD
	char	**argv;
	t_vec	redirections;
	t_vec	assignments;
};

/*
** NOTE: pipeline represented by [] t_proc represented by ()
**    t_lexer represented by {}
** {[(foo bar) | (baz)]; [(far bor)] && [(boz)]}
*/

struct		s_cmd
{
	t_proc	*pipeline;
	pid_t	pgid;
	int		(*condition)(int); //NOTE: OR AND etc
	int		background;
	t_cmd	*next;
};

struct		s_build
{
	t_cmd	*head;
	t_cmd	*work;
	t_proc	*work_proc;
	t_u64	expected_type; //NOTE: used for syntax errors
};

/*
** Prototypes
*/

int			build_tree(t_lexer *lexer, t_cmd **result);
int			exec_tree(t_sh *shell, t_cmd *tree);

int			apply_newline(t_token *token, t_build *build);
int			apply_ampersand(t_token *token, t_build *build);
int			apply_dampersand(t_token *token, t_build *build);
int			apply_dampersand(t_token *token, t_build *build);
int			apply_dpipe(t_token *token, t_build *build);
int			apply_pipe(t_token *token, t_build *build);
int			apply_word(t_token *token, t_build *build);
int			apply_io_nb(t_token *token, t_build *build);
int			apply_redir(t_token *token, t_build *build);

/*
** Utils
*/

int			cmd_new(t_cmd **cmd);
int			proc_new(t_proc **proc);
int			or_condition(int last_ret_code);
int			and_condition(int last_ret_code);
void		free_tree(t_cmd *cmd);
int			proc_is_empty(t_proc *proc);
int			cmd_is_empty(t_cmd *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:45:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 15:01:21 by wbraeckm         ###   ########.fr       */
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

typedef struct s_proc	t_proc;
typedef struct s_cmd	t_cmd;
typedef struct s_build	t_build;

/*
** Structures
*/

struct		s_proc
{
	t_cmd	*parent;
	t_proc	*next;
	pid_t	pid;
	int		argc;
	char	**argv;
	//TODO: add build stuff (i e: tokens related to this command)
	t_vec	*tokens; //NOTE: not final
};

struct		s_cmd
{
	t_proc	*pipeline;
	pid_t	pgid;
	int		(*condition)(t_sh*); //NOTE: OR AND etc
	t_cmd	*next;
};

struct		s_build
{
	t_cmd	*head;
	t_cmd	*work;
};

/*
** Prototypes
*/

t_cmd		*build_tree(t_sh *shell, t_lexer *lexer);
int			exec_tree(t_sh *shell, t_cmd *tree);

#endif

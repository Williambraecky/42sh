/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 18:51:12 by wbraeckm         ###   ########.fr       */
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

/*
** Defines
*/

# define SH_IN 0
# define SH_OUT 1
# define SH_ERR 2
# define INTERACTIVE 0
# define NON_INTERACTIVE 1

/*
** Typedefs
*/

typedef struct s_sh	t_sh;
typedef struct stat	t_stat;
typedef struct termios	t_termi;

/*
** Structures
*/

struct		s_sh
{
	t_map	*env;
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

int			copy_env(t_sh *shell, const char **env);

/*
**  Utils
*/

void		free_sh(t_sh *shell);
int			init_interactive_mode(t_sh *shell);
void		ignore_signal(int signo);

#endif

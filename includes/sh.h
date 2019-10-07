/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 18:00:06 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*
** Includes
*/

# include <unistd.h>
# include <signal.h>
# include "libft.h"

/*
** Typedefs
*/

typedef struct s_sh	t_sh;
typedef struct stat	t_stat;

/*
** Structures
*/

struct		s_sh
{
	t_map	*env;
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

#endif

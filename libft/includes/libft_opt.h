/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_opt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:07:19 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/10 16:44:39 by tcastron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_OPT_H
# define LIBFT_OPT_H

/*
** Full getopt implementation (man getopt) (WIP)
*/

# include "libft.h"

/*
** Defines
*/

# define NO_ARG 0
# define REQ_ARG 1
# define OPT_ARG 2

/*
** Typedefs
*/

typedef struct s_option	t_option;

/*
** Structures
*/

struct		s_option
{
	char	*name;
	int		has_arg;
	int		*flag;
	int		val;
};

/*
** Prototypes
*/

int			ft_getopt(int argc, char **argv, const char *optstring);
int			ft_getopt_long(int argc, char **argv, const char *optstring,
	t_option *longopts);
int			ft_getopt_long_only(int argc, char **argv, const char *optstring,
	t_option *longopts);
void		ft_reset_opt(void);

#endif

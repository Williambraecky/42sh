/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:53 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/10 16:43:39 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "sys/types.h"
# include "sys/stat.h"
# include "unistd.h"
# include "sh.h"

int			int_cmp(char *s1, char *s2, char *cmp_op);
int			not_op_reverse(int ret, int not_op);
int			cmp_op(char **av, int ac, int not_op);
int			test_op(char op, char **av, int ac, int not_op);

#endif

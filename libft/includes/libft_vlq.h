/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_vlq.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:52:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 18:17:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_VLQ_H
# define LIBFT_VLQ_H

# include "libft.h"

# define _NOMSB_ 0x7FFFFFFFFFFFFFFF

typedef t_u64*	t_vlq;

t_vlq	ft_vlqnew(size_t len);
size_t	ft_vlqlen(t_vlq vlq);
int		ft_vlqcmp(t_vlq a, t_vlq b);
void	ft_vlqdel(t_vlq *vlq);
t_vlq	ft_vlqdup(t_vlq vlq);
t_vlq	ft_vldadd(t_vlq a, t_vlq b);
void	ft_vlqtrim(t_vlq *vlq);
t_vlq	ft_binstrtovlq(const char *str);
void	ft_vlqadd_set(t_vlq *vlq, t_vlq b);
t_vlq	ft_vlqof(t_u64 value);
t_u32	ft_vlq_count_actbits(t_vlq vlq);
t_u32	ft_vlq_count_actbits(t_vlq vlq);

#endif

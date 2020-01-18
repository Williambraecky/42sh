/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bparam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 00:06:31 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 00:07:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_bparam(t_bparam *bparam)
{
	ft_strdel(&bparam->key);
	ft_strdel(&bparam->word);
	ft_strdel(&bparam->result);
}

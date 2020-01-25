/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_handle_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:44:53 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 22:35:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	fc_print_history(t_fc *fc, size_t line_nb, char *command)
{
	if (!fc->opt_n)
		ft_printf("%zu", line_nb);
	ft_printf("\t");
	ft_putnonprint(command);
	ft_printf("\n");
}

int			fc_handle_l(t_sh *shell, t_fc *fc)
{
	size_t	*range;
	size_t	i;
	size_t	max;

	max = fc->first >= fc->last ?
		fc->first - fc->last + 1 : fc->last - fc->first + 1;
	range = fc_make_range(fc->first, fc->last);
	i = fc->opt_r ? max : 0;
	while (range && (fc->opt_r ? i-- : i < max))
	{
		fc_print_history(fc, range[i] + 1,
			ft_vecget(&shell->history, range[i]));
		if (!fc->opt_r)
			i++;
	}
	free(range);
	return (0);
}

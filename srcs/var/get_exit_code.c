/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:49:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:49:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_exit_code(t_sh *shell)
{
	char	*var;

	if (get_var(shell, "?", &var) == SH_SUCCESS)
		return (ft_atoi(var));
	return (0);
}

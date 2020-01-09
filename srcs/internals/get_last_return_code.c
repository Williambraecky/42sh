/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_return_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:45:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/09 15:46:47 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: since ? is a read only value for users it should always be present
*/

int		get_last_return_code(t_sh *shell)
{
	char	*var;

	get_internal(shell, "?", &var);
	return (ft_atoi(var));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:41:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 17:42:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		or_condition(int last_ret_code)
{
	return (last_ret_code != 0);
}

int		and_condition(int last_ret_code)
{
	return (last_ret_code == 0);
}

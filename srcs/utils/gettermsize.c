/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettermsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:10:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/15 19:13:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_winsiz	gettermsize(void)
{
	t_winsiz	winsize;

	ioctl(0, TIOCGWINSZ, &winsize);
	return (winsize);
}

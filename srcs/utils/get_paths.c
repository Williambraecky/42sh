/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:24:47 by ntom              #+#    #+#             */
/*   Updated: 2019/10/23 16:28:24 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_paths(t_sh *shell, char ***paths)
{
	char	*str;

	str = NULL;
	paths = NULL;
	if (get_env(shell, "PATH", &str) != SH_SUCCESS)
		return (SH_ERR_NOEXIST);
	if (!(*paths = ft_strsplit(str, ':')))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

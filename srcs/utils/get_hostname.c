/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 02:52:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:55:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_hostname_short(t_sh *shell)
{
	char	*hostname;
	char	*dot;

	hostname = get_hostname(shell);
	if (!hostname)
		return (NULL);
	if ((dot = ft_strchr(hostname, '.')))
		*dot = '\0';
	return (hostname);
}

char	*get_hostname(t_sh *shell)
{
	char	*hostname;

	if (get_var_clone(shell, "HOST", &hostname) == SH_SUCCESS)
		return (hostname);
	if (!(hostname = ft_strnew(256)))
		return (NULL);
	if (gethostname(hostname, 256) != 0)
	{
		free(hostname);
		return (NULL);
	}
	add_var(shell, "HOST", hostname);
	return (hostname);
}

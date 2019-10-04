/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_join_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:17:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/04 16:18:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab_join_fd(char **tab, char *joiner, int fd)
{
	while (*tab)
	{
		write(fd, *tab, ft_strlen(*tab));
		if (tab[1] && (ft_strlen(*tab) || JOIN_EMPTY))
			write(fd, joiner, ft_strlen(joiner));
		tab++;
	}
}

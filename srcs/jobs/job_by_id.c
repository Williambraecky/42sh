/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_by_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:13:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 19:51:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	strcontains(char *a, char *b)
{
	return (ft_strstr(a, b) != NULL);
}

t_cmd		*job_by_id(t_sh *shell, char *id)
{
	int		(*cmp_func)();
	size_t	len;

	if (shell->jobs.size == 0 || !id)
		return (NULL);
	else if (ft_strstartswith(id, "%%") || ft_strstartswith(id, "%+"))
		return (ft_vecgettop(&shell->jobs));
	else if (ft_strstartswith(id, "%-"))
		return (ft_vecget(&shell->jobs, ft_min(shell->jobs.size - 2, 0)));
	else if (ft_strisnumber(id + 1))
		return (ft_vecget(&shell->jobs, ft_atoi(id + 1)));
	cmp_func = ft_strstartswith;
	if (*id == '%')
		id++;
	if (*id == '?')
	{
		id++;
		cmp_func = strcontains;
	}
	len = shell->jobs.size;
	while (len--)
		if (cmp_func(((t_cmd*)ft_vecget(&shell->jobs, len))->cmd_str, id))
			return (ft_vecget(&shell->jobs, len));
	return (NULL);
}

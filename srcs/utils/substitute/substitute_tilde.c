/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 20:54:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:51:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"
#include <pwd.h>
#include <uuid/uuid.h>

static void	prefix_tilde(t_subst *subst, size_t j)
{
	char			*tmp;
	char			*home;
	struct passwd	*pwnam;

	if (!(tmp = ft_strndup(subst->str + subst->i, j)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	pwnam = getpwnam(tmp + 1);
	if (pwnam)
		home = pwnam->pw_dir;
	else
		home = tmp;
	subst->err = buff_append(&subst->buffer, home);
	free(tmp);
	subst->i += j;
}

static void	basic_tilde(t_subst *subst)
{
	char			*home;
	struct passwd	*pwnam;

	home = NULL;
	if (get_var(subst->shell, "HOME", &home) != SH_SUCCESS)
		pwnam = getpwent();
	if (!home && pwnam)
		home = pwnam->pw_dir;
	if (!home)
		subst->err = buff_append(&subst->buffer, "~");
	else
		subst->err = buff_append(&subst->buffer, home);
	subst->i++;
}

/*
** NOTE: at this point the format is validated to be correct
*/

void		substitute_tilde(t_subst *subst)
{
	size_t	j;

	j = subst->i;
	while (subst->str[j] != '/' && subst->str[j] && subst->str[j] != ' ' &&
			subst->str[j] != '\t' && subst->str[j] != '\n' &&
			(!(subst->profile & SUB_ASSIGN) || subst->str[j] != ':'))
		j++;
	j -= subst->i;
	if (j == 1)
		basic_tilde(subst);
	else
		prefix_tilde(subst, j);
}

/*
** NOTE: SUB_ASSIGN allows for tilde to be preceded by = or :
*/

int			tilde_check(t_subst *subst, size_t j)
{
	size_t	i;

	if (!(subst->profile & SUB_TILDE))
		return (0);
	if (j != 0 && !(subst->profile & SUB_ASSIGN))
		return (0);
	if (j != 0 && subst->str[j - 1] != ':' &&
		is_escaped(&subst->stack, subst->str, j - 1))
		return (0);
	i = j;
	while (subst->str[i] != '/' && subst->str[i] && subst->str[i] != ' ' &&
			subst->str[i] != '\t' && subst->str[i] != '\n' &&
			(!(subst->profile & SUB_ASSIGN) || subst->str[i] != ':'))
	{
		if (is_escaped(&subst->stack, subst->str, i))
			return (0);
		i++;
	}
	return (1);
}

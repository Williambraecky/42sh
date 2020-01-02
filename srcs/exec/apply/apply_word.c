/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 19:03:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 19:23:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	can_be_assign(t_token *token, t_build *build)
{
	char	*equals;
	int		is_name;

	if (build->work_proc->unprocessed_argv.size > 0)
		return (0);
	equals = ft_strchr(token->str, '=');
	if (!equals)
		return (0);
	*equals = '\0';
	is_name = str_is_name(token->str);
	*equals = '=';
	return (is_name);
}

static int	apply_assignment(t_token *token, t_build *build)
{
	(void)token;
	(void)build;
	return (SH_SUCCESS);
}

static int	check_redir_filename(t_token *token, t_build *build)
{
	t_redir	*redir;

	redir = (t_redir*)ft_vecgettop(&build->work_proc->redirections);
	if (!redir || redir->filename)
		return (0);
	redir->filename = token->str;
	return (SH_SUCCESS);
}

int			apply_word(t_token *token, t_build *build)
{
	if (check_redir_filename(token, build) == SH_SUCCESS)
		return (SH_SUCCESS);
	if (can_be_assign(token, build))
		return (apply_assignment(token, build));
	if (ft_vecpush(&build->work_proc->unprocessed_argv, token))
		return (SH_ERR_MALLOC);
	build->work_proc->argc++;
	return (SH_SUCCESS);
}

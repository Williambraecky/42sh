/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 19:03:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 01:47:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	if (ft_veccpush(&build->work_proc->assignments,
		token->str, ft_strlen(token->str) + 1))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static int	check_redir_filename(t_token *token, t_build *build)
{
	t_redir	*redir;

	redir = (t_redir*)ft_vecgettop(&build->work_proc->redirections);
	if (!redir || redir->filename)
		return (0);
	redir->filename = token->str;
	return (1);
}

static int	apply_redir_filename(t_token *token, t_build *build)
{
	t_redir	*redir;

	redir = (t_redir*)ft_vecgettop(&build->work_proc->redirections);
	if (!(redir->filename = ft_strdup(token->str)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int			apply_word(t_token *token, t_build *build, t_lexer *lexer)
{
	if (check_redir_filename(token, build) == 1)
		return (apply_redir_filename(token, build));
	if (can_be_assign(token, build))
		return (apply_assignment(token, build));
	if (ft_veccpush(&build->work_proc->unprocessed_argv,
		token->str, token->len + 1))
		return (SH_ERR_MALLOC);
	if (lexer->can_be_alias == 1)
		lexer->can_be_alias = 0;
	else if (lexer->can_be_alias == 2)
		lexer->can_be_alias = 1;
	return (SH_SUCCESS);
}

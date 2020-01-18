/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:06:59 by ntom              #+#    #+#             */
/*   Updated: 2020/01/18 16:00:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			init_lexer(t_sh *shell, t_lexer *lexer, char *line)
{
	int		block;

	block = lexer->block_sigtstp;
	ft_bzero(lexer, sizeof(*lexer));
	lexer->block_sigtstp = block;
	if (init_build_tree(&lexer->build))
		return (SH_ERR_MALLOC);
	lexer->build.work_proc->block_sigtstp = block;
	if (ft_vecinit(&lexer->tokens))
		return (SH_ERR_MALLOC);
	if (!(lexer->alias_stack = ft_memalloc(sizeof(char*) *
		(shell->aliases->size + 1))))
		return (SH_ERR_MALLOC);
	if (!(lexer->line = ft_strdup(line)) ||
		!(lexer->clean_line = ft_strdup(line)))
		return (SH_ERR_MALLOC);
	lexer->line_size = ft_strlen(line);
	lexer->can_be_alias = 1;
	if (ft_vecinit_size(&lexer->stack, ft_strlen(lexer->line) / 2))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int			lexer(char *line, t_lexer *lexer, t_sh *shell)
{
	int			res;

	if ((res = init_lexer(shell, lexer, line)) != SH_SUCCESS)
		return (res);
	res = tokenization(lexer, shell);
	return (res);
}

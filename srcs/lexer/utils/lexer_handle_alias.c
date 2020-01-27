/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_alias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 23:04:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:14:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		alias_stack_clear(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (lexer->alias_stack[i])
		ft_strdel(&(lexer->alias_stack[i++]));
}

int			alias_stack_contains(t_lexer *lexer, char *str)
{
	size_t	i;

	i = 0;
	while (lexer->alias_stack[i])
		if (ft_strequ(lexer->alias_stack[i++], str))
			return (1);
	return (0);
}

static void	alias_stack_add(t_lexer *lexer, char *str)
{
	size_t	i;

	i = 0;
	while (lexer->alias_stack[i])
		i++;
	lexer->alias_stack[i] = str;
}

int			lexer_handle_alias(t_sh *shell, t_lexer *lexer, char *str)
{
	char	*aliased;
	char	*line;

	aliased = get_alias(shell, str);
	alias_stack_add(lexer, str);
	if (!(line = ft_strnew(ft_strlen(lexer->line) - ft_strlen(str) +
		ft_strlen(aliased))))
		return (SH_ERR_MALLOC);
	if (aliased[ft_strlen(aliased) - 1] == ' ')
		lexer->can_be_alias = 2;
	ft_strncpy(line, lexer->line, lexer->i);
	ft_strcat(line + lexer->i, aliased);
	ft_strcat(line + lexer->i + ft_strlen(aliased),
		lexer->line + lexer->i + ft_strlen(str));
	free(lexer->line);
	lexer->line = line;
	return (SH_SUCCESS);
}

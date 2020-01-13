/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_alias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 23:04:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 00:22:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

static void	alias_stack_pop(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (lexer->alias_stack[i])
		i++;
	if (i)
		lexer->alias_stack[i - 1] = NULL;
}

/*
** TODO: Maybe we call tokenization from here instead of replacing line
** TODO: further improve aliases
*/

int			lexer_handle_alias(t_sh *shell, t_lexer *lexer, char *str)
{
	char	*aliased;
	char	*line;
	size_t	i;
	int		ret;
	int		no_start;

	if (!(aliased = ft_strdup(get_alias(shell, str))))
		return (SH_ERR_MALLOC);
	alias_stack_add(lexer, str);
	no_start = lexer->no_start;
	lexer->no_start = 1;
	line = lexer->line;
	i = lexer->i;
	lexer->line = aliased;
	lexer->i = 0;
	ret = tokenization(lexer, shell);
	alias_stack_pop(lexer);
	lexer->can_be_alias = aliased[ft_strlen(aliased) - 1] == ' ';
	lexer->no_start = no_start;
	lexer->line = line;
	lexer->i = i + ft_strlen(str);
	free(str);
	free(aliased);
	return (ret);
}

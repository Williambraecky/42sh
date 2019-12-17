/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:21:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 17:31:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: Should aliases be store as token list or as string?
** NOTE: Resolving should be recursive but not loop indefinitely
**  (ie alias a=b; alias b=a => a -> a)
*/

static int	used_contains(char **used, char *str)
{
	size_t	i;

	i = 0;
	while (used[i])
		if (used[i++] == str)
			return (1);
	return (0);
}

static void	set_used(char **used, char *str)
{
	size_t	i;

	i = 0;
	while (used[i])
		i++;
	used[i] = str;
}

/*
** NOTE: Untested af really not sure about the logic
*/

int			resolve_alias(t_sh *shell, char *alias, t_vec **tokens)
{
	char	**used;
	t_alias	*alias_t;

	if (!(used = ft_memalloc(sizeof(*used) * ft_mapsize(shell->aliases))))
		return (SH_ERR_MALLOC);
	alias_t = get_alias(shell, alias);
	while (has_alias(shell, ((t_token*)alias_t->tokens->vec[0])->str)
		&& !used_contains(used, alias_t->str))
	{
		set_used(used, alias_t->str);
		alias_t = get_alias(shell, ((t_token*)alias_t->tokens->vec[0])->str);
	}
	free(used);
	if (!alias_t)
		return (SH_ERR_NOEXIST);
	*tokens = alias_t->tokens;
	return (SH_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:21:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/26 21:28:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** TODO: make sure it passes through the delimiter
*/

static char	*delim_proxy(char *str)
{
	t_lexer	lexer;
	char	*delim;

	if (init_lexer(&lexer, str) != SH_SUCCESS)
		return (NULL);
	if (delimit_token(&lexer, &delim) != SH_SUCCESS)
	{
		lexer_free(&lexer);
		return (NULL);
	}
	lexer_free(&lexer);
	return (delim);
}

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
		if (ft_strequ(used[i++], str))
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
** NOTE: delimited string does not process parameter expansion etc
*/

static int	resolve_recurs(t_sh *shell, char **used,
	char *alias, char **return_val)
{
	char	*delimited;
	int		ret;

	if (used_contains(used, alias))
		return (SH_SUCCESS);
	*return_val = get_alias(shell, alias);
	if (!(delimited = delim_proxy(*return_val)))
		return (SH_ERR_MALLOC);
	set_used(used, alias);
	ret = SH_SUCCESS;
	if (has_alias(shell, delimited))
		ret = resolve_recurs(shell, used, delimited, return_val);
	free(delimited);
	return (ret);
}

int			resolve_alias(t_sh *shell, char *alias, char **return_val)
{
	char	**used;
	int		ret;

	if (!(used = ft_memalloc(sizeof(*used) * (ft_mapsize(shell->aliases) + 1))))
		return (SH_ERR_MALLOC);
	ret = resolve_recurs(shell, used, alias, return_val);
	free(used);
	return (ret);
}

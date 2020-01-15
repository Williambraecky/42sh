/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:57:17 by ntom              #+#    #+#             */
/*   Updated: 2020/01/15 14:02:51 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		free_struct(t_brace *brace, int ret)
{
	ft_strdel(&brace->param);
	ft_strdel(&brace->param_expand);
	ft_strdel(&brace->word);
	return (ret);
}

int		init_struct(t_brace *brace, t_sh *shell, char *str, char **result)
{
	char	*tmp;

	brace->shell = shell;
	brace->str = str;
	brace->result = result;
	brace->hashtag = str[1] == '#' ? 1 : 0;
	get_key((brace->str + brace->hashtag + 1), &brace->param);
	if ((brace->param_status = get_internal(shell, brace->param, &tmp)) != 0)
		brace->param_status = get_env(shell, brace->param, &tmp);
	expand_no_brace(brace->shell, brace->param,
		&brace->param_expand, brace->len);
	if (get_op(str + ft_strlen(brace->param) + 1 + brace->hashtag
		, &brace->op, brace->len) != 0)
		return (SH_ERR_BAD_SUBST);
	get_word((str + *brace->len + brace->hashtag + 1), &brace->word);
	what_op_does(brace->param_status, brace->op, &brace->what_op);
	*brace->len = 0;
	while (str[*brace->len]
		&& (str[*brace->len] != '}' || is_char_escaped(str, *brace->len)))
		*brace->len += 1;
	*brace->len += 1;
	if (!brace->param || !brace->param_expand || !brace->word)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

void	init_expand_param(size_t *i, size_t *len, int *quoted, char **result)
{
	*i = 0;
	*len = 0;
	*quoted = 0;
	*result = NULL;
}

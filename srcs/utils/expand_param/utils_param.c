/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:55:51 by ntom              #+#    #+#             */
/*   Updated: 2020/01/15 13:57:06 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_charset(char c, int first_char)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9' && first_char != FIRST_CHAR)
			|| c == '_');
}

int		join_expanded(char *str, size_t *dollar, char **result, size_t len)
{
	char	tmp_c;
	char	*tmp_str;

	tmp_c = str[*dollar - 1];
	str[*dollar - 1] = '\0';
	tmp_str = ft_strjoin(str, *result);
	str[*dollar - 1] = '$';
	if (!tmp_str)
		return (SH_ERR_MALLOC);
	ft_strdel(result);
	*result = tmp_str;
	*result = ft_strjoin(tmp_str, str + *dollar + len);
	ft_strdel(&tmp_str);
	if (!*result)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

void	what_op_does(int status, char op, int *what_op)
{
	if (op == 0)
		*what_op = DO_NOTHING;
	else if (op == '%')
		*what_op = REMOVE_SUFFIX;
	else if (op == '#')
		*what_op = REMOVE_PREFIX;
	else
	{
		if ((status == 0 && op == '+') || (status != 0 && op == '-'))
			*what_op = SUBST_WORD;
		else if (status == 0)
			*what_op = SUBST_PARAM;
		else if ((status != 0 && op == '='))
			*what_op = ASSIGN_WORD;
		else if ((status != 0 && op == '+'))
			*what_op = SUBST_NULL;
		else if ((status != 0 && op == '?'))
			*what_op = ERROR_EXIT;
	}
}

int		do_op(t_brace *brace)
{
	int		ret;

	if (brace->what_op == SUBST_PARAM)
		*brace->result = ft_strdup(brace->param_expand);
	else if (brace->what_op == SUBST_NULL)
		*brace->result = ft_strdup("");
	else if (brace->what_op == ASSIGN_WORD || brace->what_op == SUBST_WORD)
	{
		*brace->result = ft_strdup(brace->word);
		if (brace->what_op == ASSIGN_WORD && (SH_SUCCESS !=
			(ret = (repl_internal(brace->shell, brace->param, brace->word)))))
			return (ret);
	}
	else if (brace->what_op == ERROR_EXIT)
		ft_dprintf(2, "42sh: %s: %s\n", brace->param, brace->word);
	else if (brace->what_op == REMOVE_SUFFIX)
		remove_suffix(brace);
	else if (brace->what_op == REMOVE_PREFIX)
		remove_prefix(brace);
	else if (brace->what_op == DO_NOTHING)
		*brace->result = brace->param_expand != NULL ?
			ft_strdup(brace->param_expand) : ft_strdup(brace->param);
	if (!*brace->result && brace->what_op != ERROR_EXIT)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

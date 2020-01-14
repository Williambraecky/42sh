/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:23:53 by ntom              #+#    #+#             */
/*   Updated: 2020/01/14 23:33:12 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#define FIRST_CHAR 0
#define SUBST_WORD 0
#define SUBST_PARAM 1
#define ASSIGN_WORD 2
#define SUBST_NULL 3
#define ERROR_EXIT 4
#define REMOVE_SUFFIX 5
#define REMOVE_PREFIX 6
#define DO_NOTHING 7

int		is_charset(char c, int first_char)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9' && first_char != FIRST_CHAR)
			|| c == '_');
}

int		get_valid_param(t_sh *shell, char *str, char **result, size_t *len)
{
	size_t	j;
	int		ret;
	char	tmp_c;

	j = 0;
	ret = SH_SUCCESS;
	while (str[j] && is_charset(str[j], j))
		j++;
	tmp_c = str[j];
	str[j] = '\0';
	if ((ret = get_internal(shell, str, result)) != SH_SUCCESS)
		ret = get_env(shell, str, result);
	str[j] = tmp_c;
	*len = j;
	return (ret);
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

int		expand_no_brace(t_sh *shell, char *str, char **result, size_t *len)
{
	char	*expand;
	int		ret;

	expand = NULL;
	ret = get_valid_param(shell, str, &expand, len);
	if (ret != SH_SUCCESS)
		expand = "";
	if (!(*result = ft_strdup(expand)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		get_opt(char *str, char *op, size_t *len)
{
	if (str[0] == '}')
	{
		op = 0;
		return (SH_SUCCESS);
	}
	if ((str[0] == ':'
		&& (str[1] == '-' || str[1] == '+' || str[1] == '?' || str[1] == '='))
		|| (str[0] == '%' && str[1] == '%') || (str[0] == '#' && str[1] == '#'))
	{
		*op = str[1];
		*len += 2;
	}
	else if (str[0] == '#' || str[0] == '%')
	{
		*op = str[0];
		*len += 1;
	}
	else if (str[0] != '}')
	{
		ft_dprintf(2, "42sh: %s: bad substitution\n", str);
		return (SH_ERR_BAD_SUBST);
	}
	return (SH_SUCCESS);
}

int		get_key(char *str, char **result)
{
	size_t	i;
	char	tmp_c;

	i = 0;
	while (str[i] && is_charset(str[i], i))
		i++;
	tmp_c = str[i];
	str[i] = '\0';
	*result = ft_strdup(str);
	str[i] = tmp_c;
	return (*result == NULL ? SH_ERR_MALLOC : SH_SUCCESS);
}

int		get_word(char *str, char **result, t_brace *brace)
{
	size_t	i;
	char	tmp_c;
	// char	*tmp;
	// int		ret;

	(void)brace;
	i = 0;
	while (str[i] && str[i] != '}' && !is_char_escaped(str, i))
	{
		// if (str[i] == '$')
		// {
		// 	tmp_c = str[i];
		// 	str[i] = '\0';
		// 	ret = expand_param(brace->shell, str, &tmp);
		// 	*result = ft_strjoin(str, tmp);
		// 	str[i] = tmp_c;
		// 	ft_strdel(&tmp);
		// 	if (ret != SH_SUCCESS || !*result)
		// 		return (SH_ERR_MALLOC);
		// }
		i++;
	}
	tmp_c = str[i];
	str[i] = '\0';
	*result = ft_strdup(str);
	str[i] = tmp_c;
	return (*result == NULL ? SH_ERR_MALLOC : SH_SUCCESS);
}

void	what_do(int status, char op, int *what_op)
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
	if (get_opt(str + ft_strlen(brace->param) + 1 + brace->hashtag
		, &brace->op, brace->len) != 0)
		return (SH_ERR_BAD_SUBST);
	get_word((str + *brace->len + brace->hashtag + 1), &brace->word, brace);
	what_do(brace->param_status, brace->op, &brace->what_op);
	*brace->len = 0;
	while (str[*brace->len]
		&& (str[*brace->len] != '}' || is_char_escaped(str, *brace->len)))
		*brace->len += 1;
	*brace->len += 1;
	if (!brace->param || !brace->param_expand || !brace->word)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		remove_prefix(t_brace *brace)
{
	size_t	i;

	i = 0;
	while (brace->param_expand[i] && brace->word[i]
		&& brace->param_expand[i] == brace->word[i])
		i++;
	*brace->result = ft_strdup(brace->param_expand + i);
	return (SH_SUCCESS);
}
int		remove_suffix(t_brace *brace)
{
	size_t	len_w;
	size_t	len_p;
	char	tmp_c;

	len_w = ft_strlen(brace->word);
	len_p = ft_strlen(brace->param_expand);
	while (brace->word[len_w] && brace->param_expand[len_p])
	{
		len_w--;
		len_p--;
	}
	tmp_c = brace->param_expand[len_p];
	brace->param_expand[len_p] = '\0';
	*brace->result = ft_strdup(brace->param_expand);
	brace->param_expand[len_p] = tmp_c;
	return (SH_SUCCESS);
}
int		do_opt(t_brace *brace)
{
	int		ret;

	if (brace->what_op == SUBST_WORD)
		*brace->result = ft_strdup(brace->word);
	else if (brace->what_op == SUBST_PARAM)
		*brace->result = ft_strdup(brace->param_expand);
	else if (brace->what_op == SUBST_NULL)
		*brace->result = ft_strdup("");
	else if (brace->what_op == ASSIGN_WORD)
	{
		*brace->result = ft_strdup(brace->word);
		if ((ret = (repl_internal(brace->shell, brace->param, brace->word)))
			!= SH_SUCCESS)
			return (ret);
	}
	else if (brace->what_op == ERROR_EXIT)
		ft_dprintf(2, "42sh: %s: %s\n", brace->param, brace->word); //todo parameter not set
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

void	free_struct(t_brace *brace)
{
	ft_strdel(&brace->param);
	ft_strdel(&brace->param_expand);
	ft_strdel(&brace->word);
}

int		expand_brace(t_sh *shell, char *str, char **result, size_t *len)
{
	t_brace	brace;
	int		ret;
	char	*tmp;

	ft_bzero(&brace, sizeof(brace));
	brace.len = len;
	if ((ret = init_struct(&brace, shell, str, result)) != SH_SUCCESS)
		return (ret);
	if ((ret = do_opt(&brace)) != SH_SUCCESS)
		return (ret);
	if (brace.hashtag == 1)
	{
		tmp = *brace.result;
		*result = ft_itoa(ft_strlen(*brace.result));
		ft_strdel(&tmp);
	}
	free_struct(&brace);
	if (!*result)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

// TODO leak

int		expand_param(t_sh *shell, char *str, char **result)
{
	size_t	i;
	size_t	len;
	int		quoted;
	int		ret;

	i = 0;
	len = 0;
	quoted = 0;
	ret = SH_SUCCESS;
	*result = NULL;
	while (str[i])
	{
		str[i] == '\'' ? quoted = !(quoted) : 0;
		if (str[i] == '$' && !(is_char_escaped(str, i)) && quoted == 0 && ++i)
		{
			if (str[i] == '{')
				ret = expand_brace(shell, str + i, result, &len);
			else if (!(is_charset(str[i], FIRST_CHAR)))
				*result = "$";
			else
				ret = expand_no_brace(shell, str + i, result, &len);
			if (ret != SH_SUCCESS
				|| (ret = join_expanded(str, &i, result, len)) != SH_SUCCESS)
				return (ret);
		}
		i++;
	}
	if (*result == NULL)
		if (!(*result = ft_strdup(str)))
			return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:51:07 by ntom              #+#    #+#             */
/*   Updated: 2020/01/15 17:31:19 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

int		expand_brace(t_sh *shell, char *str, char **result, size_t *len)
{
	t_brace	brace;
	int		ret;
	char	*tmp;

	ft_bzero(&brace, sizeof(brace));
	brace.len = len;
	if ((ret = init_struct(&brace, shell, str, result)) != SH_SUCCESS)
		return (free_struct(&brace, ret));
	if ((ret = do_op(&brace)) != SH_SUCCESS)
		return (free_struct(&brace, ret));
	if (brace.hashtag == 1)
	{
		tmp = *brace.result;
		*result = ft_itoa(ft_strlen(*brace.result));
		ft_strdel(&tmp);
	}
	free_struct(&brace, ret);
	if (!*result)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		expand_param(t_sh *shell, char *str, char **result)
{
	size_t	i;
	size_t	len;
	int		quoted;
	int		ret;

	init_expand_param(&i, &len, &quoted, result);
	while (str != NULL && str[i])
	{
		str[i] == '\'' ? quoted = !(quoted) : 0;
		if (str[i] == '$' && !(is_char_escaped(str, i)) && quoted == 0 && ++i
			&& (str[i] == '{' || is_charset(str[i], FIRST_CHAR)))
		{
			if (str[i] == '{')
				ret = expand_brace(shell, str + i, result, &len);
			else
				ret = expand_no_brace(shell, str + i, result, &len);
			if (ret != SH_SUCCESS
				|| (ret = join_expanded(str, &i, result, len)) != SH_SUCCESS)
				return (ret);
		}
		i++;
	}
	if (*result == NULL && (str == NULL || !(*result = ft_strdup(str))))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

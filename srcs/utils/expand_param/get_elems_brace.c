/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems_brace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:53:43 by ntom              #+#    #+#             */
/*   Updated: 2020/01/15 13:56:35 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

int		get_op(char *str, char *op, size_t *len)
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

int		get_word(char *str, char **result)
{
	size_t	i;
	char	tmp_c;

	i = 0;
	while (str[i] && str[i] != '}' && !is_char_escaped(str, i))
		i++;
	tmp_c = str[i];
	str[i] = '\0';
	*result = ft_strdup(str);
	str[i] = tmp_c;
	return (*result == NULL ? SH_ERR_MALLOC : SH_SUCCESS);
}

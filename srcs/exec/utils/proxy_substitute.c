/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:48:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 20:13:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: use real substitute function
*/

/*
** static int		handleparam(t_sh *shell, char *str, char **result, size_t *len)
** {
** 	size_t	i;
** 	int		ret;
**
** 	i = 0;
** 	//to do str is null
** 	if (*str == '$' && !(is_char_escaped(str, 0)) && ++i
** 		&& (str[i] == '{' || is_charset(str[i], FIRST_CHAR)))
** 	{
** 		if (str[i] == '{')
** 			ret = expand_brace(shell, str + i, result, len);
** 		else
** 			ret = expand_no_brace(shell, str + i, result, len);
** 		if (ret != SH_SUCCESS
** 			|| (ret = join_expanded(str, &i, result, *len)) != SH_SUCCESS)
** 			return (ret);
** 	}
** 	return (SH_SUCCESS);
** }
**
** static int		handletilde(t_sh *shell, char *str, char **result, size_t *len)
** {
** 	int		ret;
**
** 	if (((ret = expand_tilde(shell, str, result))) != SH_SUCCESS)
** 		return (ret);
** 	*len += ft_strlen(*result);
** 	return (SH_SUCCESS);
** }
**
** int				remove_quotes(t_sh *shell, char *str, char **result)
** {
** 	size_t	i;
** 	t_type	quote;
** 	size_t	len;
** 	int		ret;
** 	char	*expanded;
** 	char	*tmp;
** 	char	tmp_c;
**
** 	quote = T_NULL;
** 	i = 0;
** 	if (str[i] != '~')
** 		expanded = ft_strdup(str);
** 	else
** 		if ((ret = handletilde(shell, str + i, &expanded, &i) != SH_SUCCESS))
** 			return (ret);
** 	while (expanded[i])
** 	{
** 		*result = NULL;
** 		if (!is_quoted(expanded, i, quote) && is_special_char(expanded, i))
** 		{
** 			quote = get_special_type(expanded, i++, quote);
** 			continue ;
** 		}
** 		if (!is_quoted(expanded, i, quote) && expanded[i] == '$')
** 		{
** 			if ((ret = handleparam(shell, expanded + i, result, &len) != SH_SUCCESS))
** 				return (ret);
** 			tmp_c = expanded[i];
** 			expanded[i] = '\0';
** 			tmp = ft_strdup(expanded);
** 			expanded[i] = tmp_c;
** 			expanded = ft_strjoin(expanded, *result);
** 			ft_strdel(&tmp);
** 			i += len;
** 		}
** 		else
** 			i++;
** 		if (*result != NULL)
** 			ft_strdel(result);
** 	}
** 	*result = expanded;
** 	return (SH_SUCCESS);
** }
*/

// int	proxy_substitute(t_sh *shell, char *str, char **result)
// {
// 	size_t	i;
// 	//char	*tmp;
// 	size_t	len;
// 	//char	*tmp2;
// 	int		ret;
// 	int		quoted;
//
// 	i = 0;
// 	while (str[i])
// 	{
// 		str[i] == '\'' ? quoted = !(quoted) : 0;
// 		if (str[i] == '$' && !(is_char_escaped(str, i)) && quoted == 0 && ++i
// 			&& (str[i] == '{' || is_charset(str[i], FIRST_CHAR)))
// 		{
// 			if (str[i] == '{')
// 				ret = expand_brace(shell, str + i, result, &len);
// 			else
// 				ret = expand_no_brace(shell, str + i, result, &len);
// 			if (ret != SH_SUCCESS
// 				|| (ret = join_expanded(str, &i, result, len)) != SH_SUCCESS)
// 				return (ret);
// 		}
// 		else if (str[i] == '~' && !(is_char_escaped(str, i)) && quoted == 0)
// 			;
// 		else if (str[i] == '\'')
// 			;
// 	}
// 	remove_quotes(*result, result);
// 	return (SH_SUCCESS);
// }

int	proxy_substitute(t_sh *shell, char *str, char **result)
{
	(void)shell;
	if (expand_param(shell, str, result) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (remove_quotes(*result, result));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:23:53 by ntom              #+#    #+#             */
/*   Updated: 2020/01/13 22:05:01 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** 	TO DO :
** 	brackets not single quoted and not escaped
** 	replace value even if non existent (empty str)
** 	braceparam inside braceparam : do stack treatment, recursively
** 	$expression
** 	order of information:
** 			parameter set and not null,
** 			parameter set but null,
** 			parameter unset
**	$parameter:			substitute parameter
**	${#parameter}:		strlen
** 	${parameter:-word}:	substitute parameter/ substitute word/ substitute word
** 	${parameter:=word}:	substitute parameter/ assign word/ assign word
** 	${parameter:?word}:	substitute parameter/ error, exit/ error, exit
** 	${parameter:+word}:	substitute word/ substitute null/ substitute null
** 	${parameter%}	replace smallest suffix
** 	${parameter%%}	replace largest suffix
** 	${parameter#}	replace smallest prefix
** 	${parameter##}	replace largest prefix
*/

#define FIRST_CHAR 1

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
	if ((ret = get_env(shell, str, result)) != SH_SUCCESS)
		ret = get_internal(shell, str, result);
	str[j] = tmp_c;
	*len = j;
	ft_printf("*len = %d, j = %d\n", *len, j);
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
	*result = tmp_str;
	*result = ft_strjoin(tmp_str, str + *dollar + len);
	ft_strdel(&tmp_str);
	if (!*result)
		return (SH_ERR_MALLOC);
	//ft_printf("str = %s, result = %s, str+d+l = %s, len = %d\n", str, *result, str + *dollar + len, len);
	return (SH_SUCCESS);
}

int		expand_brace(t_sh *shell, char *str, char **result, size_t *i)
{
	(void)str;
	(void)shell;
	(void)result;
	(void)i;
	return(SH_SUCCESS);
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
	return(SH_SUCCESS);
}

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
	while (str[i])
	{
		str[i] == '\'' ? quoted = !(quoted) : 0 ;
		if (str[i] == '$' && !(is_char_escaped(str, i)) && quoted == 0 && ++i)
		{
			ft_printf("ret = %d\n", is_charset(str[i], FIRST_CHAR));
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
	return (SH_SUCCESS);
}

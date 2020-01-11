/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:23:53 by ntom              #+#    #+#             */
/*   Updated: 2020/01/11 17:49:46 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** 	TO DO :
** 	[a-zA-Z_][a-zA-Z0-9_]* charset for parameter
** 	brackets not single quoted and not escaped
** 	replace value even if non existent (empty str)
** 	braceparam inside braceparam : do stack treatment, recursively
** 	$expression
** 	order of information:
** 			parameter set and not null,
** 			parameter set but null,
** 			parameter unset
** 	${parameter:-word}:	substitute parameter/ substitute word/ substitute word
** 	${parameter:=word}:	substitute parameter/ assign word/ assign word
** 	${parameter:?word}:	substitute parameter/ error, exit/ error, exit
** 	${parameter:+word}:	substitute word/ substitute null/ substitute null
** 	${#parameter}	strlen of parameter
** 	${parameter%}	replace smallest suffix
** 	${parameter%%}	replace largest suffix
** 	${parameter#}	replace smallest prefix
** 	${parameter##}	replace largest prefix
*/

#define FIRST_CHAR 1
#define NOT_FIRST_CHAR 0

int		is_charset(char c, int first_char)
{
	return ((c > 'a' && c < 'z')
			|| (c > 'A' && c < 'Z')
			|| (c > '0' && c < '9' && first_char == NOT_FIRST_CHAR)
			|| c == '_');
}

int		get_valid_parameter(t_sh *shell, char *str, size_t *len, char **result)
{
	size_t	i;
	char	tmp;
	int		ret;

	i = 0;
	ret = SH_SUCCESS;
	if (!(is_charset(str[i], FIRST_CHAR)))
		return (ret);
	i++;
	while (str[i] && is_charset(str[i], NOT_FIRST_CHAR))
		i++;
	tmp = str[i];
	str[i] = '\0';
	*len = ft_strlen(str) + 1;
	if ((ret = get_env(shell, str, result)) != SH_SUCCESS)
		ret = get_internal(shell, str, result);
	str[i] = tmp;
	return (ret);
}

int		expand_brace_param(t_sh *shell, char *str, char **result)
{
	(void)shell;
	(void)str;
	(void)result;
	return (SH_SUCCESS);
}

int		expand_no_brace(t_sh *shell, char *str, char **result)
{
	char	*expanded;
	size_t	key_len;
	int		ret;

	(void)result;
	ret = SH_SUCCESS;
	if ((ret = get_valid_parameter(shell, str + 1, &key_len, &expanded)
		!= SH_SUCCESS))
		return (ret);
	if (!(*result = ft_strjoin(expanded, str + key_len)))
		return (SH_ERR_MALLOC);
	ft_printf("expanded %s, key %zu, result %s\n", expanded, key_len, *result);
	return (SH_SUCCESS);
}

int		expand_param(t_sh *shell, char *str, char **result)
{
	int		ret;
	int		i;
	char	*tmp;

	ret = SH_SUCCESS;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] != '$')
		return (SH_SUCCESS);
	if ((str + i)[1] == '{')
		ret = expand_brace_param(shell, str + i, result);
	else
		ret = expand_no_brace(shell, str + i, result);
	tmp = *result;
	str[i] = '\0';
	if (ret != SH_SUCCESS)
	{
		if (!(*result = ft_strdup(str)))
		{
			ft_strdel(&tmp);
			return (SH_ERR_MALLOC);
		}
	}
	else if (!(*result = ft_strjoin(str, *result)))
	{
		ft_strdel(&tmp);
		return (SH_ERR_MALLOC);
	}
	str[i] = '$';
	ft_strdel(&tmp);
	ft_printf("find = %s\n", str + i);
	return (SH_SUCCESS);
}

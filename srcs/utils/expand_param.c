/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:23:53 by ntom              #+#    #+#             */
/*   Updated: 2020/01/14 03:28:42 by ntom             ###   ########.fr       */
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
	//ft_printf("str = %s, result = %s, str+d+l = %s, len = %d\n", str, *result, str + *dollar + len, len);
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

int		get_opt(char *str, char *op, size_t *len, int *status)
{
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
		return (SH_ERR_BAD_SUBST);
	if ((*status == 0 && *op == '+') || (*status != 0 && *op == '-'))
		*status = 0; // substitute word
	else if (*status == 0)
		*status = 1; //substitute parameter
	else if ((*status != 0 && *op == '='))
		*status = 2; // assign word
	else if ((*status != 0 && *op == '+'))
		*status = 3; // substitute null
	else if ((*status != 0 && *op == '?'))
		*status = 4; // error exit
	return (SH_SUCCESS);
}

int		get_good_param(char *str, size_t *len, char **param, int *status)
{
	if (*status == 1)
		return (SH_SUCCESS);
	ft_strdel(param);
	if (*status == 0 || *status == 2)
		*param = ft_strdup(str + (*len - 1));
	else if (*status == 3 || *status == 4)
		*param = ft_strdup("");
	// TODO maybe add status 4 with weird error print sometime
	if (!(*param))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		operator(char *str, size_t *len, char **param, int *status)
{
	char	op;

	if (get_opt(str + (*len) - 1, &op, len, status) != SH_SUCCESS)
		return (SH_ERR_BAD_SUBST);
	get_good_param(str, len, param, status);
	return (SH_SUCCESS);
}

// 0 found and not empty
// 1 found and empty
// 2 not found

int		do_op(int status, char **param, t_sh *shell, char **result)
{
	int		ret;

	if (status == 1)
		*result = ft_strdup(*param);
	else if (status == 0)
	{
		ft_printf("param = %s\n", *param);
		if ((ret = get_internal_clone(shell, *param, result)) != SH_SUCCESS)
			if ((ret =get_env_clone(shell, *param, result)) != SH_SUCCESS)
				if (!(*result = ft_strdup(*param)))
					return (SH_ERR_MALLOC);
	}
	else if (status == 2)
		*result = ft_strdup(*param); //add internal to do
	else if (status == 3)
		*result = ft_strdup("");
	ft_strdel(param);
	if (!(*result))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

void 	calculate_len(size_t *len, char *str)
{
	while (str + *len && (str + *len)[0] != '}')
		*len += 1;
	*len += 1;
}

int		expand_brace(t_sh *shell, char *str, char **result, size_t *len)
{
	int		status;
	char	*param;
	int		hashtag;

	(void)result;
	param = NULL;
	hashtag = 0;
	if (str[1] == '#')
		hashtag = 1;
	if ((expand_no_brace(shell, str + hashtag + 1, &param, len)) == SH_SUCCESS)
		status = (ft_strlen(param) == 0);
	else
		status = 2;
	*len += 1;
	if (str[(*len)++] == '}')
	{
		*result = param;
		return (SH_SUCCESS);
	}
	operator(str, len, &param, &status);
	do_op(status, &param, shell, result);
	//TODO hashtag itoa strlen instead
	calculate_len(len, str);
	return (SH_SUCCESS);
}

// TODO Some cases where closing brackets is added when substitute word
// check leaks
// do norm
// fuck this horrible code

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
	return (SH_SUCCESS);
}

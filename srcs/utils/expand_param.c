/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:23:53 by ntom              #+#    #+#             */
/*   Updated: 2020/01/11 14:21:53 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//	TO DO :
//	[a-zA-Z_][a-zA-Z0-9_]* charset for parameter
//	brackets not single quoted and not escaped
//	replace value even if non existent (empty str)
//	braceparam inside braceparam : do stack treatment, recursively
//	$expression
//	order of information:
//			parameter set and not null,
//			parameter set but null,
//			parameter unset
//	${parameter:-word}:	substitute parameter/ substitute word/ substitute word
//	${parameter:=word}:	substitute parameter/ assign word/ assign word
//	${parameter:?word}:	substitute parameter/ error, exit/ error, exit
//	${parameter:+word}:	substitute word/ substitute null/ substitute null
//	${#parameter}	strlen of parameter
//	${parameter%}	replace smallest suffix
//	${parameter%%}	replace largest suffix
//	${parameter#}	replace smallest prefix
//	${parameter##}	replace largest prefix

int		expand_brace_param(char **str)
{
	(void)str;
	return (SH_SUCCESS);
}

int		expand_param(t_sh *shell, char *str, char **result)
{
	int		ret;
	char	*find;

	(void)shell;
	(void)str;
	(void)result;
	if (!(find = ft_strchr(str, '$')))
		return (SH_SUCCESS);
	if (find[1] == '{')
		if ((ret = expand_brace_param(&find)) != SH_SUCCESS)
			return (ret);

	ft_printf("find = %s\n", find);
	return (SH_SUCCESS);
}

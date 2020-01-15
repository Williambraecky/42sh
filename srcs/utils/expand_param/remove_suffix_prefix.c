/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_suffix_prefix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:03:08 by ntom              #+#    #+#             */
/*   Updated: 2020/01/15 14:07:41 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		remove_suffix(t_brace *brace)
{
	size_t	len_w;
	size_t	len_p;
	char	tmp_c;

	len_w = ft_strlen(brace->word) - 1;
	len_p = ft_strlen(brace->param_expand) - 1;
	while (brace->word[len_w] && brace->param_expand[len_p]
		&& brace->word[len_w] == brace->param_expand[len_p])
	{
		len_w--;
		len_p--;
	}
	tmp_c = brace->param_expand[len_p + 1];
	brace->param_expand[len_p + 1] = '\0';
	*brace->result = ft_strdup(brace->param_expand);
	brace->param_expand[len_p + 1] = tmp_c;
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

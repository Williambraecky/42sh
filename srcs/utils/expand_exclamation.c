/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:11:26 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/14 20:49:17 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

int		is_quoted(char *str, size_t i, t_type quote)
{
	if (quote == T_QUOTE)
		return (str[i] != '\'');
	else if (quote == T_DOUBLE_QUOTE)
		return (is_char_escaped(str, i) || str[i] == '\'');
	return (is_char_escaped(str, i));
}

int		get_lastmatch(t_sh *shell, char *str, char **result)
{
	size_t	i;

	i = 0;
	while (i < shell->history.size)
	{
		if (ft_strstartswith(shell->history.vec[i], str))
		{
			*result = ft_strjoin(shell->history.vec[i], (str + 2));
			return (SH_SUCCESS);
		}
		++i;
	}
	return (SH_ERR_NOEXIST);
}

int		get_lasti(t_sh *shell, char *str, char **result, int rev)
{
	char	*index;
	size_t	i;
	int		ret;
	int		pos;

	index = str;
	i = 0;
	while (!ft_isdigit(index[i]))
		++i;
	index = index + i;
	pos = (!rev) ? ft_atoi(index) : shell->history.size - ft_atoi(index);
	if (pos < 0 || pos > (int)shell->history.size - 1)
	{
		ft_dprintf(2, "sh : no such event: %s\n", (str + 2));
		return (SH_ERR_OPEN_HIST);
	}
	ret = get_history(shell, pos, result);
	while (ft_isdigit(index[i]))
		++i;
	if (index + i)
		*result = ft_strjoin(*result, (index + i));
	return (ret);
}

int		expand_exclamation(t_sh *shell, char *line, char **res)
{
	size_t	i;
	char		*tmp;
	int			ret;

	if (!line || shell->history.size > 0 || !is_quoted(line, 0, T_QUOTE))
		return (SH_SUCCESS);
	i = 0;
	if (!(tmp = ft_strdup(line)))
		return (SH_ERR_MALLOC);
	ret = SH_SUCCESS;
	while (i < ft_strlen(tmp) && ret == SH_SUCCESS)
	{
		if (tmp[i] == '!' && tmp[i + 1] != '\n' && tmp[i + 1] != '\0' && tmp[i + 1] != '\"')
		{
			if (tmp[i + 1] == '!')
				ret = get_history(shell, shell->history.size - 1, res);
			else if (tmp[0] == '!' && ft_isalpha(tmp[1]))
				ret = get_lastmatch(shell, tmp, res);
			else if (tmp[0] == '!' && ft_isdigit(tmp[1]))
				ret = get_lasti(shell, tmp, res, 0);
			else if (tmp[0] == '!' && tmp[1] == '-' && ft_isdigit(tmp[2]))
				ret = get_lasti(shell, tmp, res, 1);
			else
			{
				ft_dprintf(2, "sh: event not found: %s\n", ((tmp + i) + 1));
				ret = SH_SUCCESS;
			}
			if (ret == SH_SUCCESS)
			{
				ft_strdel(&tmp);
				tmp = ft_strdup(*res);
				ft_strdel(res);
				i = 0;
			}
		}
		++i;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:11:26 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/12 22:54:32 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_lastmatch(t_sh *shell, char *str, char **result)
{
	size_t	i;

	i = 0;
	while (i < shell->history.size)
	{
		if (ft_strstartswith(shell->history.vec[i], str))
		{
			*result = ft_strdup(shell->history.vec[i]);
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
	ft_printf("pos = %d\n", pos);
	if (pos < 0 || pos > (int)shell->history.size - 1)
	{
		ft_dprintf(2, "sh : no such event: %s\n", (str + 2));
		return (SH_ERR_OPEN_HIST);
	}
	ret = get_history(shell, pos, result);
	return (ret);
}

int		expand_exclamation(t_sh *shell, char *str, char **result)
{
	if (!(*result = ft_strdup(str)))
		return (SH_ERR_MALLOC);
	if (!str || str[0] != '!')
		return (SH_SUCCESS);
	else if (str[0] == '!' && (str[1] == '\n' || str[1] == '\0'))
		return (SH_SUCCESS);
	else if (str[0] == '!' && str[1] == '!')
		return (get_history(shell, shell->history.size - 1, result));
	else if (str[0] == '!' && ft_isalpha(str[1]))
		return (get_lastmatch(shell, str, result));
	else if (str[0] == '!' && ft_isdigit(str[1]))
		return (get_lasti(shell, str, result, 0));
	else if (str[0] == '!' && str[1] == '-' && ft_isdigit(str[2]))
		return (get_lasti(shell, str, result, 1));
	else
		ft_dprintf(2, "sh: event not found: %s\n", (str + 1));
	return (SH_SUCCESS);
}
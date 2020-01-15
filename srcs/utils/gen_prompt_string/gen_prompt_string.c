/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:41:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 17:29:29 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** TODO: should we implement something like this or hardcode the prompt?
** NOTE: main procedure for substituting PS1
** NOTE: not as fancy as bash's; handles \h \H \u \w \W
** \h   The hostname, up to the first . (e.g. deckard)
** \H   The hostname. (e.g. deckard.SS64.com) $HOST
** \w   The current working directory.
** \W   The basename of $PWD.
** \u   The username of the current user. $USER
*/

char			*g_tab_chars[] =
{
	['h'] = "HOST",
	['H'] = "HOST",
	['w'] = "PWD",
	['W'] = "PWD",
	['u'] = "USER"
};

static int	do_w(t_sh *shell, char **result)
{
	if (!(*result = getpwd_short(shell)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static int	do_h(char **result)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = *result;
	while ((*result)[i] && (*result)[i] != '.')
		i++;
	(*result)[i] = '\0';
	if (!(*result = ft_strdup(*result)))
		return (SH_ERR_MALLOC);
	tmp[i] = '.';
	return (SH_SUCCESS);
}

static int	expand_char(t_sh *shell, char c, char **result)
{
	char	*get;

	if ((get_internal(shell, g_tab_chars[(int)c], &get) != SH_SUCCESS))
	{
		if ((get_env(shell, g_tab_chars[(int)c], &get)) != SH_SUCCESS)
		{
			if (!(*result = ft_strdup("")))
				return (SH_ERR_MALLOC);
			return (SH_SUCCESS);
		}
	}
	if (c == 'h')
		do_h(&get);
	if (c == 'w')
		do_w(shell, &get);
	if (!get)
		return (SH_ERR_MALLOC);
	if (!(*result = ft_strdup(get)))
		return (SH_ERR_MALLOC);
	if (c == 'h' || c == 'w')
		ft_strdel(&get);
	return (SH_SUCCESS);
}

static int	replace_esc(t_sh *shell, char **str, char c, size_t i)
{
	char	*begining;
	char	*ending;
	char	*expand;
	char	*tmp;
	int		ret;

	(*str)[i - 1] = '\0';
	begining = ft_strdup(*str);
	(*str)[i - 1] = '\\';
	if (!begining)
		return (SH_ERR_MALLOC);
	if ((ret = expand_char(shell, c, &expand)) != SH_SUCCESS)
	{
		ft_strdel(&begining);
		return (ret);
	}
	tmp = ft_strjoin(begining, expand);
	ft_strdel(&begining);
	ft_strdel(&expand);
	if (!tmp || !(ending = ft_strdup((*str) + i + 1)))
		return (SH_ERR_MALLOC);
	*str = ft_strjoin(tmp, ending);
	ft_strdel(&tmp);
	ft_strdel(&ending);
	return ((*str) ? SH_SUCCESS : SH_ERR_MALLOC);
}

int			gen_prompt_string(t_sh *shell, char *ps1, char **result)
{
	char	*prompt;
	char	*tmp;
	int		ret;
	size_t	i;

	ret = SH_SUCCESS;
	i = 0;
	if (ps1 == NULL)
		prompt = ft_strdup("");
	else
	{
		ret = expand_param(shell, ps1, &prompt);
		while (prompt[i] && (tmp = prompt))
		{
			if (is_valid_esc(prompt, &i))
			{
				ret = replace_esc(shell, &prompt, prompt[i], i);
				ft_strdel(&tmp);
				if (ret != SH_SUCCESS)
					return (ret);
			}
			i++;
		}
	}
	return (end_gen_prompt(ret, result, prompt));
}

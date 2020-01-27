/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_prompt_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:41:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:18:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: main procedure for substituting PS1
** NOTE: not as fancy as bash's; handles \h \H \u \w \W
** \h   The hostname, up to the first . (e.g. deckard)
** \H   The hostname. (e.g. deckard.SS64.com) $HOST
** \w   The current working directory.
** \W   The basename of $PWD.
** \u   The username of the current user. $USER
** \g   The current git branch in a "(%s) " format
** \j   The current number of jobs handled by the shell
*/

static char		*g_handled = "hHwWugj";

static int		get_append(t_sh *shell, char c, char **result)
{
	if (c == 'W')
		*result = getpwd_short(shell);
	else if (c == 'w')
		*result = getpwd(shell);
	else if (c == 'u')
	{
		if (!has_var(shell, "USER"))
			*result = ft_strdup("");
		else
			get_var_clone(shell, "USER", result);
	}
	else if (c == 'h')
		*result = get_hostname_short(shell);
	else if (c == 'H')
		*result = get_hostname(shell);
	else if (c == 'g')
		*result = get_git_branch(shell);
	else if (c == 'j')
		*result = ft_uitoa(shell->jobs.size);
	if (!*result)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static int		handle(t_sh *shell, t_buff *buffer, char c)
{
	char	*append;
	int		ret;

	ret = get_append(shell, c, &append);
	if (append != NULL)
		ret = buff_append(buffer, append);
	free(append);
	return (ret);
}

static int		handle_esc(t_sh *shell, t_buff *buffer, char *ps1, char **next)
{
	char	*format;

	format = ft_strchr(g_handled, ps1[1]);
	if (!format || *format == '\0')
	{
		*next = ps1 + 1;
		return (buff_nappend(buffer, ps1, 1));
	}
	*next = ps1 + 2;
	return (handle(shell, buffer, *format));
}

static size_t	next_esc(t_sh *shell, t_buff *buffer, char *ps1, int *ret)
{
	char	*next;

	next = ft_strchr(ps1, '\\');
	if (!next)
	{
		*ret = buff_append(buffer, ps1);
		return (ft_strlen(ps1));
	}
	else
	{
		*ret = buff_nappend(buffer, ps1, next - ps1);
		if (*ret == SH_SUCCESS)
			*ret = handle_esc(shell, buffer, next, &next);
	}
	return (next - ps1);
}

int				gen_prompt_string(t_sh *shell, char *ps1, char **result)
{
	t_buff	buffer;
	size_t	i;
	int		ret;

	if (buff_init(&buffer) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	ret = SH_SUCCESS;
	if (ps1 == NULL)
		ps1 = "\\W > ";
	i = 0;
	while (*ps1 && ret == SH_SUCCESS)
		ps1 += next_esc(shell, &buffer, ps1, &ret);
	if (ret == SH_SUCCESS)
		ret = substitute(shell, buffer.buffer, result, ~SUB_ASSIGN);
	free(buffer.buffer);
	return (ret);
}

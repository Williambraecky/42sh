/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:11:46 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/08 14:12:31 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: The fc utility shall list, or shall edit and re-execute,
** commands previously entered to an interactive sh.
*/

static int	list_commands(t_sh *shell, int start, int rev, int nonumber)
{
	int		i;
	int		count;

	if (shell == NULL || !shell->history.vec)
		return (1);
	i = (rev) ? shell->history.size : start;
	count = 0;
	while (shell->history.vec[i])
	{
		if (count >= 15)
			break ;
		if (nonumber)
			ft_printf("s\n", shell->history.vec[i]);
		else
			ft_printf("%n  %s\n", i, shell->history.vec[i]);
		i = (rev && i > start) ? i - 1 : i + 1;
		++count;
	}
	return (0);
}

static int	get_last_command(t_sh *shell, int rev, char **command)
{
	int	ret;
	size_t	pos;

	if (!shell)
		return (SH_ERR_NOEXIST);
	pos = (rev) ? 0 : shell->history.size - 1;
	ret = get_history(shell, pos, command);
	return (ret && remove_history(shell, pos));
}

static int	fc_parser(int argc, char **argv, char *activ_opt)
{
	char	c;

	ft_bzero(activ_opt, 5);
	while ((c = ft_getopt(argc, argv, "elnrs")) != -1)
	{
		if (c == 'e')
			ft_strcat(activ_opt, "e");
		else if (c == 'l')
			ft_strcat(activ_opt, "l");
		else if (c == 'n')
			ft_strcat(activ_opt, "n");
		else if (c == 'r')
			ft_strcat(activ_opt, "r");
		else if (c == 's')
			ft_strcat(activ_opt, "s");
		else
			return (NO_ARG);
			// still need "not valid arg to handle"
	}
	return (0);
}

int			fc_builtin(int argc, char **argv, t_sh *shell)
{
	char	opt[5];
	char	*command;

	if (fc_parser(argc, argv, opt) > 0)
		return (shell || SH_ERR_NOEXIST);
	if (ft_strlen(opt) == 0 || ft_strchr(opt, 'e'))
	{
		get_last_command(shell, (ft_strchr(opt, 'r')) ? 1 : 0, &command);
		return (0);
	}
	else if (ft_strchr(opt, 'l'))
	{
		if (ft_strchr(opt, 'r'))
			list_commands(shell, 0, 1, (ft_strchr(opt, 'n')) ? 1 : 0);
		else
			list_commands(shell, 0, 0, (ft_strchr(opt, 'n')) ? 1 : 0);
	}
	else if (ft_strchr(opt, 's'))
	{
		get_last_command(shell, (ft_strchr(opt, 'r')) ? 1 : 0, &command);
		return (0);
	}
	return (0);
}

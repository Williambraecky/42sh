/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:11:46 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/14 23:36:12 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: The fc utility shall list, or shall edit and re-execute,
** commands previously entered to an interactive sh.
*/

/*
static int	vecgetlastmatch_index(t_vec *vec, char *find)
{
	int 	i;

	i = vec->size - 1;
	while (i >= 0 && i < vec->size)
	{
		if (ft_strstartswith(vec->vec[i], find))
			return (i);
		--i;
	}
	return (-1);
}

static int	simple_list(t_sh *shell, int start, int end, int rev, int nonumber)
{
	int		i;

	if (shell == NULL || !shell->history.vec)
		return (SH_ERR);
	i = (rev) ? end : start;
	while (start <= i && end >= i)
	{
		if (nonumber)
			ft_printf("s\n", shell->history.vec[i]);
		else
			ft_printf("%n  %s\n", i, shell->history.vec[i]);
		i = (rev) ? i - 1 : i + 1;
	}
	return (SH_SUCCESS);
}

static int			fc_l_option(t_sh *shell, char *opt, char *f, char *l)
{
	int		start;
	int		end;
	int		rev;

	rev = 0;
	start = 0;
	end = shell->history.size - 1;
	if (f)
	{
		if ((start = vecgetlastmatch_index(&shell->history, f)) == -1)
			return (SH_ERR);
	}
	if (l)
	{
		if ((end = vecgetlastmatch_index(&shell->history, l)) == -1)
			return (SH_ERR);
	}
	if (ft_strchr(opt, 'r'))
		rev = 1;
	simple_list(shell, start, end, rev, (ft_strchr(opt, 'n')) ? 1 : 0);
	return (SH_SUCCESS);
}

static int	fc_s_option(t_sh *shell, char *opt, char **old_new)
{

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

static int	fc_parser(int ac, char **av, char *opt, char **f, char **l)
{
	char		c;
	size_t	i;

	ft_bzero(opt, 5);
	i = 1;
	while (i < (size_t)ac)
	{
		if (!ft_strchr(av[i], '-') && !ft_strchr(av[i], '='))
		{
			*f = av[i];
			*l = av[i + 1];
			break;
		}
		++i;
	}
	while ((c = ft_getopt(ac, av, "elnrs")) != -1)
	{
		if (c == 'e' && !ft_strchr(opt, 'e'))
			ft_strcat(opt, "e");
		else if (c == 'l' && !ft_strchr(opt, 'l'))
			ft_strcat(opt, "l");
		else if (c == 'n' && !ft_strchr(opt, 'n'))
			ft_strcat(opt, "n");
		else if (c == 'r' && !ft_strchr(opt, 'r'))
			ft_strcat(opt, "r");
		else if (c == 's' && !ft_strchr(opt, 's'))
			ft_strcat(opt, "s");
		else
			return (NO_ARG);
	}
	return (0);
}

int			fc_builtin(int argc, char **argv, t_sh *shell)
{
	char	opt[5];
	char	*command;
	char	*f;
	char	*l;
	char	**old_new;
	int		i;

	f =  NULL;
	l = NULL;
	if (fc_parser(argc, argv, opt, &f, &l) > 0)
		return (SH_ERR_NOEXIST);
	i = 0;
	while (i < (size_t)argc)
	{
		(!ft_strchr(av[i], '-') && ft_strchr(av[i], '='))
			old_new = ft_strsplit(argv[i], '=');
	}
	if (ft_strlen(opt) == 0 || ft_strchr(opt, 'e'))
	{
		get_last_command(shell, (ft_strchr(opt, 'r')) ? 1 : 0, &command);
		return (0);
	}
	else if (ft_strchr(opt, 'l'))
	{
		fc_l_option(shell, opt, f, l);
	}
	else if (ft_strchr(opt, 's'))
	{
		get_last_command(shell, (ft_strchr(opt, 'r')) ? 1 : 0, &command);
		return (0);
	}
	return (0);
}
*/

int			fc_builtin(int argc, char **argv, t_sh *shell)
{
	(void)argc;
	(void)argv;
	(void)shell;
	return (0);
}

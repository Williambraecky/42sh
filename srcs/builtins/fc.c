/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:11:46 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/15 20:05:19 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: The fc utility shall list, or shall edit and re-execute,
** commands previously entered to an interactive sh.
*/

static int	set_options(int ac, char **av, t_fc *as)
{
	char	c;

	ft_bzero(as->opt, 5);
	while ((c = ft_getopt(ac, av, "elnrs")) != -1)
	{
		if (c == 'e' && !ft_strchr(as->opt, 'e'))
			ft_strcat(as->opt, "e");
		else if (c == 'l' && !ft_strchr(as->opt, 'l'))
			ft_strcat(as->opt, "l");
		else if (c == 'n' && !ft_strchr(as->opt, 'n'))
		{
			ft_strcat(as->opt, "n");
			as->n = 1;
		}
		else if (c == 'r' && !ft_strchr(as->opt, 'r'))
		{
			ft_strcat(as->opt, "r");
			as->rev = 1;
		}
		else if (c == 's' && !ft_strchr(as->opt, 's'))
			ft_strcat(as->opt, "s");
		else
			return (NO_ARG);
	}
	return (SH_SUCCESS);
}

static int	fc_parser(int ac, char **av, t_fc *as)
{
	int		i;
	int		ret;

	i = 1;
	ret = SH_SUCCESS;
	while (i < ac && ret == SH_SUCCESS)
	{
		if (!ft_strchr(av[i], '-') && ft_strchr(av[i], '='))
		{
			if (!(as->old_new = ft_strsplit(av[i], '=')))
				ret = SH_ERR_MALLOC;
		}
		if (!ft_strchr(av[i], '-') && !ft_strchr(av[i], '='))
		{
			as->f = av[i];
			if (av[i + 1])
				if (!ft_strchr(av[i + 1], '-') && !ft_strchr(av[i + 1], '='))
					as->l = av[i + 1];
		}
		++i;
	}
	ret = set_options(ac, av, as);
	return (ret);
}

/*
** static int	fc_s_option(t_sh *shell, t_fc *args)
** {
** 	size_t i;
**
** 	if (args->old_new)
** 	{
** 			i = 0;
** 			while ()
** 	}
** }
*/

static int	simple_list(t_sh *shell, t_fc *args, int rev, int nonumber)
{
	int		i;

	if (shell->history.size <= 0)
		return (SH_ERR_NOEXIST);
	i = (rev) ? args->end - 1 : args->start;
	while (i >= args->start && i < args->end)
	{
		if (nonumber)
			ft_printf("%s\n", shell->history.vec[i]);
		else
			ft_printf("%d  %s\n", i, shell->history.vec[i]);
		i = (rev) ? --i : ++i;
	}
	return (SH_SUCCESS);
}

static int	fc_l_option(t_sh *shell, t_fc *args)
{
	int		i;

	i = shell->history.size - 1;
	while (i >= 0 && shell->history.vec[i])
	{
		if (args->f && ft_strstartswith(shell->history.vec[i], args->f))
		{
			args->start = i;
			while (i < (int)shell->history.size)
			{
				if (args->l && ft_strstartswith(shell->history.vec[i], args->l))
				{
					args->end = i;
					break ;
				}
				++i;
			}
			break ;
		}
		--i;
	}
	simple_list(shell, args, args->rev, args->n);
	return (SH_SUCCESS);
}

static int	get_last_command(t_sh *shell, t_fc *as, char **command)
{
	int		ret;
	size_t	pos;
	int		i;

	if (!shell)
		return (SH_ERR_NOEXIST);
	i = shell->history.size - 1;
	while (as->f && i >= 0)
	{
		if (ft_strstartswith(shell->history.vec[i], as->f))
		{
			*command = ft_strdup(shell->history.vec[i]);
			if (as->old_new && ft_strstartswith(*command, as->old_new[0]))
				*command = ft_strsreplall(*command, as->old_new[0],
						as->old_new[1]);
			return ((command) ? SH_ERR_MALLOC : SH_SUCCESS);
		}
		--i;
	}
	pos = (as->rev) ? 0 : shell->history.size - 1;
	ret = get_history(shell, pos, command);
	return (ret && remove_history(shell, pos));
}

int		fc_builtin(int argc, char **argv, t_sh *shell)
{
	t_fc	*args;
	char	*command;
	int		ret;

	args = init_fc(shell);
	if (fc_parser(argc, argv, args) > 0)
		return (SH_ERR_NOEXIST);
	ft_printf("first = %s, last = %s\n", args->f, args->l);
	if (args->old_new)
		ft_printf("%s=%s\n", args->old_new[0], args->old_new[1]);
	ft_printf("start = %d end = %d\n", args->start, args->end);
	ft_printf("opt = %s\n", args->opt);
	if (ft_strchr(args->opt, 'l'))
		return (fc_l_option(shell, args));
	if (ft_strchr(args->opt, 's'))
	{
		ret = get_last_command(shell, args, &command);
		ft_printf("command = %s\n", command);
	}
	return (SH_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_read_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:48:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 22:35:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_optind;
extern int	g_optopt;
extern char	*g_optarg;

static int		fc_read_spec_opt(t_fc *fc, int getopt_ret)
{
	if (getopt_ret == 's')
	{
		fc->opt_s = 1;
		fc->s_replace = g_optarg;
	}
	else if (getopt_ret == ':')
	{
		if (g_optopt == 's')
		{
			fc->opt_s = 1;
			fc->s_replace = NULL;
		}
		else
		{
			ft_dprintf(2, "42sh: fc: -e: argument expected\n");
			return (1);
		}
	}
	else if (getopt_ret == '?' && !ft_isdigit(g_optopt))
	{
		ft_dprintf(2, "42sh: fc: -%c: invalid option\n", g_optopt);
		return (1);
	}
	return (0);
}

int				fc_read_opt(t_fc *fc, int *argc, char ***argv)
{
	int		ret;

	while ((ret = ft_getopt(*argc, *argv, ":s:lnre:")) != -1)
	{
		if (ret == 'l')
			fc->opt_l = 1;
		else if (ret == 'n')
			fc->opt_n = 1;
		else if (ret == 'r')
			fc->opt_r = 1;
		else if (ret == 'e')
		{
			fc->opt_e = 1;
			fc->editor = g_optarg;
		}
		else if (fc_read_spec_opt(fc, ret))
			return (1);
	}
	*argc -= g_optind;
	*argv += g_optind;
	if (*argc < 0)
		*argv += *argc;
	if (*argc < 0)
		*argc = 0;
	return (0);
}

static size_t	fc_index_from_str(t_sh *shell, t_fc *fc, char *str)
{
	size_t	i;

	if (fc->err)
		return (0);
	if (ft_strisnumber(str))
	{
		if (ft_atol(str) < 0 &&
			(size_t)(shell->history.size + ft_atol(str)) < shell->history.size)
			return (shell->history.size + ft_atol(str));
		else if (ft_atol(str) <= 0)
			return (shell->history.size - 1);
		return (ft_min(shell->history.size - 1, ft_atol(str) - 1));
	}
	i = shell->history.size;
	while (i--)
		if (ft_strstartswith(ft_vecget(&shell->history, i), str))
			return (i);
	ft_dprintf(2, "42sh: fc: history specification out of range\n");
	fc->err = 1;
	return (0);
}

void			fc_read_first_last(t_sh *shell, t_fc *fc,
	int argc, char **argv)
{
	if (argc == 0)
	{
		if (!fc->opt_l)
			fc->first = shell->history.size - 1;
		else
			fc->first = shell->history.size - 16;
		fc->last = shell->history.size - 1;
	}
	else if (argc == 1)
	{
		fc->first = fc_index_from_str(shell, fc, argv[0]);
		if (fc->opt_l)
			fc->last = shell->history.size - 1;
		else
			fc->last = fc->first;
	}
	else if (argc >= 2)
	{
		fc->first = fc_index_from_str(shell, fc, argv[0]);
		fc->last = fc_index_from_str(shell, fc, argv[1]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:52:57 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/23 16:42:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*g_optarg = NULL;
int			g_optind = 1;
int			g_opterr = 0;
int			g_optopt = '?';

static char	*g_optcursor;

static int	getopt_done(void)
{
	g_optcursor = NULL;
	return (-1);
}

static int	scan_opt(int argc, char **argv, const char *optstring)
{
	int		optchar;
	char	*optdecl;

	optchar = *g_optcursor;
	g_optopt = optchar;
	optdecl = ft_strchr(optstring, optchar);
	if (!optdecl)
		return ('?');
	if (optdecl[1] != ':')
		return (optchar);
	g_optarg = ++g_optcursor;
	g_optcursor = NULL;
	if (*g_optarg != '\0')
		return (optchar);
	if (optdecl[2] != ':')
	{
		if (++g_optind < argc)
			g_optarg = argv[g_optind];
		else if (!(g_optarg = NULL))
			return ((optstring[0] == ':') ? ':' : '?');
	}
	else
		g_optarg = NULL;
	return (optchar);
}

int			ft_getopt(int argc, char **argv, const char *optstring)
{
	int	optchar;

	g_optarg = NULL;
	g_opterr = 0;
	g_optopt = 0;
	if (g_optind >= argc || argv[g_optind] == NULL || *argv[g_optind] != '-' ||
		ft_strequ(argv[g_optind], "-"))
		return (getopt_done());
	if (ft_strequ(argv[g_optind], "--"))
	{
		g_optind++;
		return (getopt_done());
	}
	if (g_optcursor == NULL || *g_optcursor == '\0')
		g_optcursor = argv[g_optind] + 1;
	optchar = scan_opt(argc, argv, optstring);
	if (g_optcursor == NULL || *++g_optcursor == '\0')
		++g_optind;
	return (optchar);
}

void		ft_reset_opt(void)
{
	g_optcursor = NULL;
	g_optarg = NULL;
	g_optind = 1;
	g_opterr = 0;
	g_optopt = '?';
}

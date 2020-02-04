/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:21:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/04 18:10:44 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_optind;
extern int	g_optopt;

/*
** NOTE: prints executables currently in hash list (with usage)
*/

static void	print_hash_table(t_sh *shell)
{
	size_t		i;
	t_hashed	*hash;

	i = 0;
	if (!shell->use_hash->size)
		return ;
	ft_printf("hits    command\n");
	while (i < shell->use_hash->max_size)
	{
		if (shell->use_hash->nodes[i].is_used)
		{
			get_hash(shell, shell->use_hash->nodes[i].key, &hash);
			ft_printf("%4d    %s\n", hash->uses, hash->path);
		}
		i++;
	}
}

static void	clear_hash_table(t_sh *shell)
{
	t_node		*node;
	t_hashed	*hashed;
	size_t		i;

	i = 0;
	while (i < shell->use_hash->max_size)
	{
		if (shell->use_hash->nodes[i].is_used)
		{
			node = &shell->use_hash->nodes[i];
			hashed = node->value;
			free(hashed->path);
			ft_memdel(&node->value);
			ft_strdel(&node->key);
			node->is_used = 0;
			shell->use_hash->size--;
		}
		i++;
	}
}

static int	hash_arguments(t_sh *shell, int argc, char **argv)
{
	char	*path;
	int		err;

	err = 0;
	while (argc--)
	{
		if (resolve_path(shell, argv[argc], &path) != SH_SUCCESS)
		{
			ft_dprintf(2, "42sh: hash: %s: not found\n", argv[argc]);
			err = 1;
			continue ;
		}
		if (has_hash(shell, argv[argc]))
			reset_hash(shell, argv[argc]);
		else
		{
			if (add_hash(shell, argv[argc], path) != SH_SUCCESS)
			{
				free(path);
				return (1);
			}
		}
		free(path);
	}
	return (err);
}

int			hash_builtin(int argc, char **argv, t_sh *shell)
{
	int		r_flg;
	int		ret;

	r_flg = 0;
	while ((ret = ft_getopt(argc, argv, "r")) != -1)
	{
		if (ret == 'r')
			r_flg = 1;
		else if (ret == '?')
		{
			ft_printf("42sh: hash: -%c: invalid option\n", g_optopt);
			ft_printf("usage: hash [-r] [name...]\n");
			return (1);
		}
	}
	argc -= g_optind;
	argv += g_optind;
	if (r_flg)
		clear_hash_table(shell);
	else if (argc == 0)
		print_hash_table(shell);
	else
		return (hash_arguments(shell, argc, argv));
	return (0);
}

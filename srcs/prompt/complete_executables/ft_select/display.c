#include "prompt.h"

static void	replace_cursor(t_select *select)
{
	size_t i;

	i = 0;
	while (i <= (size_t)select->row_total - 1)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	i = 0;
	select->pos_col += select->max_len + 2;
	while (i < (size_t)select->pos_col)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
}

static int	print_poss(t_select *select, t_vec *poss, int selected, int i)
{
	size_t j;

	if (i == selected)
	{
		tputs(tgetstr("so", NULL), 1, ft_putchar);
		ft_printf("%s", ft_vecget(poss, i));
		tputs(tgetstr("se", NULL), 1, ft_putchar);
	}
	else
		ft_printf("%s", ft_vecget(poss, i));
	j = 0;
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	while (j < (size_t)select->pos_col)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		j++;
	}
	return (SH_SUCCESS);
}

int			display_poss(t_select *select, t_vec *poss, int selected)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < poss->size)
	{
		j = 0;
		while (j < (size_t)select->row_total && ft_vecget(poss, i) != NULL)
		{
			print_poss(select, poss, selected, i);
			i++;
			j++;
		}
		if (i < poss->size)
			replace_cursor(select);
	}
	return (SH_SUCCESS);
}

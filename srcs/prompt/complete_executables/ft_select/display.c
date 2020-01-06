#include "prompt.h"

/*static void	replace_cursor(t_select *select)
{
	size_t i;

	i = 0;
	while (i <= (size_t)select->row_total - 2)
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

static int	is_last_of_row(int i, t_select *select)
{
	int j;

	j = 1;
	while (j < select->elem_per_row)
	{
		if (i == (j * select->row_total) - 1)
			return (1);
		j++;
	}
	return (0);
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
	if (!is_last_of_row(i, select))
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	while (j < (size_t)select->pos_col)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		j++;
	}
	return (SH_SUCCESS);
}*/

/*int			display_poss(t_select *select, t_vec *poss, int selected)
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
}*/

int					replace_cursor(t_select *select, t_prompt *prompt)
{
	size_t	i;
	t_pos	pos;

	i = 0;
	pos.x = prompt->max_pos.x;
	pos.y = -select->row_total;
	move_cursor(pos);
	return (SH_SUCCESS);
}

static int			print_selected(t_select *select, t_vec *poss, size_t i)
{
	size_t j;

	j = 0;
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	ft_dprintf(0, "%-*s",select->max_len + 2, (char *)ft_vecget(poss, i));
	tputs(tgetstr("se", NULL), 1, ft_putchar);
	return (SH_SUCCESS);
}

int					display_poss(t_select *select, t_vec *poss, int selected,
	t_prompt *prompt)
{
	size_t i;
	size_t j;
	size_t f;

	i = 0;
	f = 0;
	ft_dprintf(0, "\n");
	while (f < (size_t)select->row_total)
	{
		j = 0;
		while (j < (size_t)select->elem_per_row)
		{
			if (i <= (size_t)select->nb_elem && ft_vecget(poss, i) != NULL)
			{
				if (i == (size_t)selected)
					print_selected(select, poss, i);
				else
					ft_dprintf(0, "%-*s",select->max_len + 2 ,(char *)ft_vecget(poss, i));
			}
			else
				break;
			j++;
			i += select->row_total;
		}
		f++;
		if (f == (size_t)select->row_total)
			break;
		ft_dprintf(0, "\n");
		i -= (select->elem_per_row * select->row_total) - 1;
	}
	replace_cursor(select, prompt);
	return (SH_SUCCESS);
}

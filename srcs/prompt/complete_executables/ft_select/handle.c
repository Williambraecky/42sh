#include "prompt.h"

int		select_handle_arrows(t_select *select, char *buffer)
{
	if (select->selected == -1)
		return (SH_SUCCESS);
	if (BUFFER == K_DOWN)
		select->selected = select->selected == select->nb_elem - 1 ? 0
		: select->selected + 1;
	else if (BUFFER == K_UP)
	{
		if (select->selected % select->row_total == 0 || select->selected == 0)
			select->selected += select->row_total - 1;
		else
			select->selected -= 1;
	}
	else if (BUFFER == K_LEFT)
	{
		if (select->selected < select->row_total)
		{
			select->selected = (select->row_total * (select->elem_per_row - 1))
				+ (select->selected % select->row_total);
			if (select->selected > select->nb_elem - 1)
				select->selected = select->nb_elem - 1;
		}
		else
			select->selected -= select->row_total;
	}
	else if (BUFFER == K_RIGHT)
	{
		if (select->selected > ((select->row_total * select->elem_per_row) - select->row_total - 1))
			select->selected %= select->row_total;
		else
		{
			select->selected += select->row_total;
			if (select->selected > select->nb_elem - 1)
				select->selected = select->nb_elem -1;
		}
	}
	return (SH_SUCCESS);
}

int		select_handle_tab(t_select *select)
{
	select->selected = select->selected == select->nb_elem - 1 ? 0
	: select->selected + 1;
	return (SH_SUCCESS);
}

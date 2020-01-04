#include "prompt.h"

//prendre un 3eme param pour les cas ou l'appel ioctl est redondant
int		get_display_info(t_select *select, t_vec *poss)
{
	t_win	win_size;
	int		len;
	size_t	i;

	ioctl(0, TIOCGWINSZ, &win_size);
	select->nb_col = win_size.ws_col;
	select->nb_row = win_size.ws_row;

	i = 0;
	select->max_len = 0;
	select->nb_elem = poss->size;
	while (i < poss->size)
	{
		len = ft_strlen((char *)ft_vecget(poss, i));
		if (len > select->max_len)
			select->max_len = len;
		i++;
	}
	get_column_info(select);
	return (SH_SUCCESS);
}

int		get_column_info(t_select *select)
{
	select->elem_per_row = (select->nb_col - 20) / select->max_len;
	select->row_total = (select->nb_elem / select->elem_per_row) + 1;
//	if (select->row_total == 0)
//		select->row_total++;
//	ft_printf("elem_per_row = %d -- row_total = %d\n", select->elem_per_row, select->row_total);
	return (SH_SUCCESS);
}

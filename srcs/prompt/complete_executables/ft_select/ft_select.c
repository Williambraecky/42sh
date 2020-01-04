#include "prompt.h"

int				erase_poss(t_select *select)
{
	size_t i;

	(void)select;
	i = 0;
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("do", NULL), 1, ft_putchar);
//	while (i < (size_t)select->row_total)
//	{
//		tputs(tgetstr("dl", NULL), 1, ft_putchar);
//		i++;
//	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	return (SH_SUCCESS);
}

static	int	get_key(t_select *select)
{
	char buffer[5];

	ft_bzero(buffer, 5);
	if (read(0, buffer, 4) < 0)
		return (-1);
	if (BUFFER == K_UP || BUFFER == K_LEFT || BUFFER == K_DOWN || BUFFER == K_RIGHT)
		select_handle_arrows(select, buffer);
	else if (BUFFER == '\t')
		select_handle_tab(select);
	else
		erase_poss(select);
	return (SH_SUCCESS);
}

int				choose_poss(t_select *select, t_vec *poss)
{
	get_display_info(select, poss);
	select->pos_col = 0;
	select->selected = -1;
	display_poss(select, poss, -1);
	while (19)
	{
		get_key(select);
		erase_poss(select);
		select->pos_col = 0;
		display_poss(select, poss, select->selected);
	}
	return (SH_SUCCESS);
}

int				ft_select(t_sh *shell, t_vec *poss)
{
	t_select select;

	init_signal();
	init_term(shell, &select);
	choose_poss(&select, poss);
//	reset_signal();
//	return (exit_erase(shell, &select));
	return (SH_SUCCESS);
}

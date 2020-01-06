#include "prompt.h"

/*int				is_cursor_position_last_row(t_select *select)
{
    int a = 0;
    int i = 0;
	int col;
	int rows;
    char buf[4];

	(void)select;
    ft_printf("\033[6n"); // string asking for the cursor position
    read(0, &buf, 1);

    while (buf[i])
    {
        if (buf[i] >= 48 && buf[i] <= 57)
        {
            if (a == 0)
                rows = atoi(&(buf[i]) - 1);
            else
                col = atoi(&(buf[i]) - 1);
            a++;
        }
        i++;
    }
	sleep(3);
	return (0);
}*/
/*
int				erase_poss(t_select *select)
{
	size_t i;

	(void)select;
	i = 0;

	tputs(tgetstr("rc", NULL), 1, ft_putchar);//ne fonctionne pas qd on est a la derniere row
//	sleep(1);

//	if (is_cursor_position_last_row(select)) //quand rc se comporte normalemnt
	tputs(tgetstr("do", NULL), 1, ft_putchar);
//	sleep(1);

	if (!is_cursor_position_last_row(select)) // quand rc ne fonctionne pas
	while (i < (size_t)select->row_total)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		i++;
	}
	sleep(1);
	tputs(tgetstr("do", NULL), 1, ft_putchar);

	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	return (SH_SUCCESS);
}
*/
/*static	int	get_key(t_select *select)
{
	char buffer[5];

	ft_bzero(buffer, 5);
	if (read(0, buffer, 4) < 0)
		return (-1);
	if (BUFFER == K_UP || BUFFER == K_LEFT || BUFFER == K_DOWN || BUFFER == K_RIGHT)
		select_handle_arrows(select, buffer);
	else if (BUFFER == '\t')
		select_handle_tab(select);
	else if (BUFFER == K_ESC)
		return (SH_SUCCESS);
	else
	{
		erase_poss(select);
//		change_line(select)
	}
	return (SH_SUCCESS);

}*/

/*int				change_line(t_select *select, t_vec *poss, t_sh *shell, t_prompt *prompt)
{
	(void)select;
	(void)shell;
	(void)poss;
	(void)prompt;
	char			*complete_command;
	size_t			i;
	size_t			len;
	static size_t	original_len;

	i = 0;
	complete_command = (char *)ft_vecget(poss, select->selected);
	len = ft_strlen(prompt->buffer.buffer);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	original_len = original_len == 0 ? len : original_len;
	while (i < len - original_len)
	{
		sleep(1);
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	i = 0;
	while (i < len - original_len)
	{
		sleep(1);
		handle_backspace(prompt, NULL, NULL);
		i++;
	}
	default_char_handler(prompt, complete_command, shell);
	return (SH_SUCCESS);
}*/

int				choose_poss(t_select *select, t_vec *poss, t_sh *shell, t_prompt *prompt)
{
	(void)select;
	(void)poss;
	(void)shell;
	(void)prompt;

	get_display_info(select, poss);
	select->pos_col = 0;
	select->selected = -1;
	display_poss(select, poss, -1, prompt);
//	while (19)
//	{
//		get_key(select);
//		change_line(select, poss, shell, prompt);
//		erase_poss(select);
//		select->pos_col = 0;
//		display_poss(select, poss, select->selected);
//	}
	return (SH_SUCCESS);
}

int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt)
{
	t_select select;

	//pas de malloc de select ?
//	init_signal();
//	init_term(shell, &select);
	select.original_pos = prompt->cursor_pos;
	choose_poss(&select, poss, shell, prompt);
//	reset_signal();
//	return (exit_erase(shell, &select));
	return (SH_SUCCESS);
}

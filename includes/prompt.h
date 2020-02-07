/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:08:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 22:00:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

/*
** Includes
*/

# include "sh.h"

/*
** Defines
*/

# define PROMPT_EXIT_SELECT -1
# define UP 4283163
# define DOWN 4348699

/*
** Typedefs
*/

typedef struct s_hquery	t_hquery;
typedef struct s_pos	t_pos;
typedef struct s_prompt	t_prompt;
typedef struct s_select	t_select;
typedef struct termios	t_termi;
typedef struct winsize	t_win;

/*
** Structures
*/

struct			s_hquery
{
	char		*query;
	char		*orig;
	size_t		curr_index;
};

struct			s_pos
{
	int			x;
	int			y;
};

struct			s_select
{
	int			nb_elem;
	int			max_len;
	int			nb_col;
	int			nb_row;
	int			selected;
	int			row_total;
	int			elem_per_row;
	int			cursor_left_len;
	int			cursor_right_len;
	int			written;
	int			shell_var_brace;
	int			file_complete;
	int			scroll;
	size_t		scroll_top;
	size_t		scroll_bottom;
	t_pos		original_pos;
	t_vec		poss;
};

/*
** buffer_index = index in buffer
** char_index = index in char (unicode char are multibytes)
** NOTE: 0: nothing 1: processed 2: select mode
*/

struct			s_prompt
{
	char		*prompt;
	t_buff		buffer;
	t_winsiz	winsize;
	size_t		valid_size;
	t_pos		cursor_pos;
	t_pos		prompt_pos;
	t_pos		max_pos;
	size_t		prompt_len;
	size_t		buffer_index;
	size_t		char_index;
	int			valid_pos;
	t_select	select;
	int			select_mode;
	int			searching;
	int			search_found;
	t_buff		search_buffer;
	t_hquery	query;
	int			querying;
	int			done;
	int			nl_offset;
	int			edit_mode;
	size_t		edit_start;
	size_t		edit_from;
	size_t		edit_to;
	char		*clipboard;
};

/*
** Prototypes
*/

/*
** Prompt
*/

int				handle_prompt(t_sh *shell, char *prompt_str, char **result);

/*
** Utils
*/

int				gen_prompt(t_sh *shell, char *prompt_str, t_prompt *prompt);
void			free_prompt(t_sh *shell, t_prompt *prompt);
size_t			wcharlen(char c);
void			move_goto(t_prompt *prompt, t_pos pos);
void			move_cursor(t_pos rel_pos);
void			move_left(t_prompt *prompt);
void			move_right(t_prompt *prompt);
void			reprint_everything(t_prompt *prompt);
void			reprint_buffer(t_prompt *prompt);
void			print_from_cursor(t_prompt *prompt, t_pos *next_pos);
t_pos			calc_prompt_pos(t_prompt *prompt);
t_pos			calc_cursor_pos(t_prompt *prompt, size_t written);
void			transform_pos(t_prompt *prompt, t_pos *pos, char c);

/*
** Handlers
*/

int				handle_new_char(t_prompt *prompt, char *buffer, t_sh *shell);
int				default_char_handler(t_prompt *prompt,
	char *buffer, t_sh *shell);
int				handle_arrows(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_newline(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_backspace(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_tab(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_escape(t_prompt *prompt, char *buffer, t_sh *shell);
int				select_handle_escape(t_prompt *prompt,
	char *buffer, t_sh *shell);
int				select_handle_newline(t_prompt *prompt,
	char *buffer, t_sh *shell);
int				select_handle_tab(t_prompt *prompt,
	char *buffer, t_sh *shell);
int				select_handle_arrows(t_prompt *prompt, char *buffer);
int				handle_shift_arrows(t_prompt *prompt, char *buffer,
	t_sh *shell);
int				handle_search(t_prompt *prompt, char *buffer, t_sh *shell);
int				search_history(t_prompt *prompt, t_sh *shell);
int				char_ignore(t_prompt *prompt, char *buffer, t_sh *shell);
int				char_empty(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_char_search(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_backspace_search(t_prompt *prompt, char *buffer,
	t_sh *shell);
void			next_line(t_prompt *prompt);
void			prev_line(t_prompt *prompt);
int				handle_edit(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_paste(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_copy(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_cut(t_prompt *prompt, char *buffer, t_sh *shell);
void			edit_move(t_prompt *prompt, char buffer_char);

/*
** History
*/

char			*hquery_cprev(t_sh *shell, t_hquery *hquery);
char			*hquery_prev(t_sh *shell, t_hquery *hquery);
char			*hquery_cnext(t_sh *shell, t_hquery *hquery);
char			*hquery_next(t_sh *shell, t_hquery *hquery);
void			search_render(t_prompt *prompt);
int				search_render_found(t_prompt *prompt, char *found);

/*
** Select
*/

char			*get_cursor_word(char *line, t_prompt *prompt);
int				get_path(t_sh *shell, char **last_word, char **path);
int				complete_command(t_sh *shell, char *s, t_vec *p);
int				autocomplete_poss(char *path, char *start, t_vec *poss);
int				autocomplete_command(char *line, t_sh *shell, t_vec *poss,
	t_prompt *prompt);
int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt);
int				get_display_info(t_select *select, t_prompt *prompt);
int				display_poss(t_select *sel, t_vec *poss, int selected,
	t_prompt *prompt);
int				print_selected(t_select *sel, t_vec *poss, int i);
int				replace_cursor(t_select *sel, t_prompt *prompt);
int				select_render(t_prompt *prompt, t_select *select);
int				change_line(t_select *select, t_prompt *prompt);
int				first_word(char *line, size_t i, size_t max, int first_word);
char			*get_brace_str(int shell_var_brace, char *line, t_prompt *p);
int				display_poss_scroll(t_select *se, t_vec *poss, int s,
	t_prompt *p);
int				posscpush(t_vec *poss, char *str, size_t len);
int				print_poss(t_vec *poss, t_select *sel, int selec, int i);

#endif

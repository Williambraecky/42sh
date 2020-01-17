/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:08:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 03:17:38 by wbraeckm         ###   ########.fr       */
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
# define PBUFF_DEF_SIZE 512
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699

/*
** Typedefs
*/

typedef struct s_hquery	t_hquery;
typedef struct s_pos	t_pos;
typedef struct s_buff	t_buff;
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

struct			s_buff
{
	char		*buffer;
	size_t		max_size;
	size_t		current_size;
};

/*
** buffer_index = index in buffer
** char_index = index in char (unicode char are multibytes)
** TODO: store max prompt pos to avoid processing everything (write pos)
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
	size_t		from_line;
	int			valid_pos;
	t_select	select;
	int			select_mode;
	t_hquery	query;
	int			querying;
	int			done;
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
void			free_prompt(t_prompt *prompt);
size_t			wcharlen(char c);
t_pos			new_calc(t_prompt *prompt, size_t written);
t_pos			new_calc_write(t_prompt *prompt, size_t written);
void			move_goto(t_prompt *prompt, t_pos pos);
void			move_cursor(t_pos rel_pos);
void			move_left(t_prompt *prompt);
void			move_right(t_prompt *prompt);
char			*wstr_remove_char(char *str, size_t index);
void			reprint_everything(t_prompt *prompt);
void			reprint_buffer(t_prompt *prompt);
void			print_from_cursor(t_prompt *prompt, t_pos *next_pos);
int				pos_equals(t_pos pos1, t_pos pos2);

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

/*
** Buffer
*/

int				buff_insert(t_buff *buffer, char *insert, size_t pos);
int				buff_remove(t_buff *buffer, size_t pos);
void			buff_clear(t_buff *buffer);

/*
** History
*/

char			*hquery_prev(t_sh *shell, t_hquery *hquery);
char			*hquery_next(t_sh *shell, t_hquery *hquery);

/*
** Select
*/

char			*get_cursor_word(char *line, t_prompt *prompt);
int				get_path(char **last_word, char **path);
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
int				first_word(char *line, size_t i, int first_word);
char			*get_brace_str(int shell_var_brace, char *line, t_prompt *p);
int				display_poss_scroll(t_select *se, t_vec *, int s, t_prompt *p);
int				posscpush(t_vec *poss, char *str, size_t len);

#endif

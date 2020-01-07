/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:08:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 18:08:10 by mpizzaga         ###   ########.fr       */
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

# define RET_CONT (1 << 0)
# define RET_NL (1 << 1)
# define RET_ERR (1 << 2)
# define RET_PRINT (1 << 3)
# define RET_REPRINT (1 << 4)
# define RET_EXIT_SELECT (1 << 5)
# define PBUFF_DEF_SIZE 512

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
	int			pos_col;
	int			written;
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
	int			select_mode; //NOTE: 0: nothing 1: processed 2: select mode
};



/*
** Prototypes
*/

int				handle_prompt(t_sh *shell, char **result);
int				gen_prompt(t_sh *shell, t_prompt *prompt);
void			free_prompt(t_prompt *prompt);
size_t			wcharlen(char c);
t_pos			new_calc(t_prompt *prompt, size_t written);
t_pos			new_calc_write(t_prompt *prompt, size_t written);
int				handle_new_char(t_prompt *prompt, char *buffer, t_sh *shell);
void			move_goto(t_prompt *prompt, t_pos pos);
void			move_cursor(t_pos rel_pos);
void			move_left(t_prompt *prompt);
void			move_right(t_prompt *prompt);
char			*wstr_remove_char(char *str, size_t index);
void			reprint_buffer(t_prompt *prompt);
void			print_from_cursor(t_prompt *prompt, t_pos *next_pos);
int				default_char_handler(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_arrows(t_prompt *prompt, char *buffer);
int				handle_newline(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_backspace(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_tab(t_prompt *prompt, char *buffer, t_sh *shell);
int				handle_escape(t_prompt *prompt, char *buffer, t_sh *shell);
int				pos_equals(t_pos pos1, t_pos pos2);
int				buff_insert(t_buff *buffer, char *insert, size_t pos);
int				buff_remove(t_buff *buffer, size_t pos);
int				count_words(char *line);
char			*get_last_word(char *line, int *space);
int				is_reset_token(char *last_word);
int				is_redirection(char *last_word);
int				get_path_last_word(char **last_word, char **path);
int				match_bin_built(t_sh *shell, char *s, t_vec *p);
int				autocomplete_poss(char *path, char *start, t_vec *poss);
int				autocomplete_command(char *line, t_sh *shell, t_vec *poss);
int				ft_select(t_sh *shell, t_vec *poss, t_prompt *prompt);
int				get_display_info(t_select *select, t_prompt *prompt);
int				display_poss(t_select *sel, t_vec *poss, int selected,
				t_prompt *prompt);
int				print_selected(t_select *sel, t_vec *poss, size_t i);
int				replace_cursor(t_select *sel, t_prompt *prompt);
int				select_handle_escape(t_prompt *prompt,
				char *buffer, t_sh *shell);
int				select_handle_newline(t_prompt *prompt,
				char *buffer, t_sh *shell);
int				select_handle_tab(t_prompt *prompt,
				char *buffer, t_sh *shell);
int				select_handle_arrows(t_prompt *prompt, char *buffer);
int				select_render(t_prompt *prompt, t_select *select);


#endif

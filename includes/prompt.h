/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:08:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/17 21:12:58 by wbraeckm         ###   ########.fr       */
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

/*
** Typedefs
*/

typedef struct s_prompt	t_prompt;
typedef struct s_pos	t_pos;

/*
** Structures
*/

struct			s_pos
{
	int			x;
	int			y;
};

/*
** buffer_index = index in buffer
** char_index = index in char (unicode char are multibytes)
*/

struct			s_prompt
{
	char		*prompt;
	char		*buffer;
	t_winsiz	winsize;
	size_t		valid_size;
	t_pos		cursor_pos;
	t_pos		prompt_pos;
	size_t		prompt_len;
	size_t		buffer_index;
	size_t		char_index;
	int			valid_pos;
};

/*
** Prototypes
*/

int				handle_prompt(t_sh *shell, char **result);
int				gen_prompt(t_sh *shell, t_prompt *prompt);
void			free_prompt(t_prompt *prompt);
size_t			wcharlen(char c);
t_pos			calc_cursor_pos(t_prompt *prompt, size_t written);
t_pos			calc_write_cursor_pos(t_prompt *prompt, size_t written);
int				handle_new_char(t_prompt *prompt, char *buffer);
void			move_cursor(t_pos rel_pos);
void			move_left(t_prompt *prompt, size_t amnt);
void			move_right(t_prompt *prompt, size_t amnt);
char			*wstr_remove_char(char *str, size_t index);
void			print_buffer(t_prompt *prompt);
void			reprint_buffer(t_prompt *prompt);

#endif

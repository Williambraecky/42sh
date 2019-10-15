/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:08:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/15 19:12:43 by wbraeckm         ###   ########.fr       */
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

/*
** Typedefs
*/

typedef struct s_prompt	t_prompt;
typedef struct s_pos	t_pos;

/*
** Structures
*/

struct		s_pos
{
	int		x;
	int		y;
};

/*
** NOTE: For cursor_pos, y = 0 is the line where we supposedly started, no way
** to correctly read current cursor position
** buffer_index = index in buffer
** char_idex = index in char (unicode char are multibytes)
*/

struct		s_prompt
{
	char	*prompt;
	char	*buffer;
	t_pos	cursor_pos;
	size_t	prompt_len;
	t_pos	relative_pos;
	size_t	buffer_index;
	size_t	char_index;
	int		valid_pos;
};

/*
** Prototypes
*/

int			handle_prompt(t_sh *shell, char **result);
int			gen_prompt(t_sh *shell, t_prompt *prompt);
void		free_prompt(t_prompt *prompt);
size_t		wcharlen(char c);

#endif

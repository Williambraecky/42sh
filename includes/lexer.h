/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:02:19 by ntom              #+#    #+#             */
/*   Updated: 2019/11/13 16:24:34 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** Includes
*/

# include "sh.h"

/*
** Defines
*/

enum		e_type
{
	GREATER,
	WSPACE,
	WORD
};

/*
** Typedefs
*/

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;
typedef enum e_type		t_type;

/*
** Structures
*/

struct		s_token
{
	char	*str;
	size_t	len;
	t_type	type;
};

struct		s_lexer
{
	t_vec	tokens;
	char	*line;
	size_t	i;
	t_vec	stack;
};

#endif

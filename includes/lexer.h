/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:02:19 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 18:11:30 by wbraeckm         ###   ########.fr       */
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
	T_NEWLINE,
	T_SEMICOLON,
	T_GREATER_AND,
	T_LESSER_AND,
	T_DOUBLE_PIPE,
	T_PIPE,
	T_DOUBLE_AMPERSAND,
	T_AMPERSAND,
	T_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOUBLE_LESSER,
	T_LESSER,
	T_DOUBLE_GREATER,
	T_GREATER,
	T_WSPACE,
	T_WORD
};

/*
** Typedefs
*/

typedef struct s_token	t_token;
typedef struct s_word	t_word;
typedef struct s_lexer	t_lexer;
typedef struct s_tdef	t_tdef;
typedef enum e_type		t_type;

/*
** Structures
*/

/*
** NOTE: size = size of real struct; used for inheritance
*/

struct		s_token
{
	size_t	size;
	t_type	type;
	char	*str;
	size_t	len;
};

struct		s_word
{
	t_token	token;
	char	*transformed;
};

struct		s_lexer
{
	t_vec	tokens;
	char	*line;
	size_t	i;
	t_vec	stack;
};

struct		s_tdef
{
	t_type	type;
	int		(*is_tok)(t_lexer *);
	int		(*create_tok)(t_lexer *);
};

/*
** Tokenization
*/

int			tokenization(t_lexer *lexer);
void		token_free(t_token *token);
int			token_process(t_lexer *lexer, t_token *token);

/*
** Tokens
*/

int			is_newline_token(t_lexer *lexer);
int			create_newline_token(t_lexer *lexer);

#endif

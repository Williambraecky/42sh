/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:02:19 by ntom              #+#    #+#             */
/*   Updated: 2019/12/08 16:41:42 by wbraeckm         ###   ########.fr       */
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

/*
** Re order e_type and g_def_table depending on priority
*/

enum		e_type
{
	T_NEWLINE,
	T_GREATER_AND,
	T_LESSER_AND,
	T_DOUBLE_PIPE,
	T_DOUBLE_AMPERSAND,
	T_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOUBLE_LESSER,
	T_LESSER,
	T_DOUBLE_GREATER,
	T_GREATER,
	T_SEMICOLON,
	T_AMPERSAND,
	T_PIPE,
	T_WSPACE,
	T_WORD,
	T_NULL
};

enum		e_tmask
{
	M_NEWLINE = 1 << T_NEWLINE,
	M_GREATER_AND = 1 << T_GREATER_AND,
	M_LESSER_AND = 1 << T_LESSER_AND,
	M_DOUBLE_PIPE = 1 << T_DOUBLE_PIPE,
	M_DOUBLE_AMPERSAND = 1 << T_DOUBLE_AMPERSAND,
	M_QUOTE = 1 << T_QUOTE,
	M_DOUBLE_QUOTE = 1 << T_DOUBLE_QUOTE,
	M_DOUBLE_LESSER = 1 << T_DOUBLE_LESSER,
	M_LESSER = 1 << T_LESSER,
	M_DOUBLE_GREATER = 1 << T_DOUBLE_GREATER,
	M_GREATER = 1 << T_GREATER,
	M_SEMICOLON = 1 << T_SEMICOLON,
	M_AMPERSAND = 1 << T_AMPERSAND,
	M_PIPE = 1 << T_PIPE,
	M_WSPACE = 1 << T_WSPACE,
	M_WORD = 1 << T_WORD,
	M_NULL = 1 << T_NULL,
	M_ANY = ~0
};

/*
** Typedefs
*/

typedef struct s_token	t_token;
typedef struct s_word	t_word;
typedef struct s_lexer	t_lexer;
typedef struct s_tdef	t_tdef;
typedef enum e_type		t_type;
typedef enum e_tmask	t_tmask;

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
	t_vec	tokens; //NOTE: Do we really need this?
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

int			istok_ampersand(t_lexer *lexer);
int			createtok_ampersand(t_lexer *lexer);
int			istok_double_ampersand(t_lexer *lexer);
int			createtok_double_ampersand(t_lexer *lexer);
int			istok_double_pipe(t_lexer *lexer);
int			createtok_double_pipe(t_lexer *lexer);
int			istok_double_quote(t_lexer *lexer);
int			createtok_double_quote(t_lexer *lexer);
int			istok_greater(t_lexer *lexer);
int			createtok_greater(t_lexer *lexer);
int			istok_greaterand(t_lexer *lexer);
int			createtok_greaterand(t_lexer *lexer);
int			istok_lesser(t_lexer *lexer);
int			createtok_lesser(t_lexer *lexer);
int			istok_lesserand(t_lexer *lexer);
int			istok_pipe(t_lexer *lexer);
int			createtok_pipe(t_lexer *lexer);
int			createtok_lesserand(t_lexer *lexer);
int			istok_quote(t_lexer *lexer);
int			createtok_quote(t_lexer *lexer);
int			istok_semicolon(t_lexer *lexer);
int			createtok_semicolon(t_lexer *lexer);
int			istok_newline(t_lexer *lexer);
int			createtok_newline(t_lexer *lexer);
int			istok_double_greater(t_lexer *lexer);
int			createtok_double_greater(t_lexer *lexer);
int			istok_double_lesser(t_lexer *lexer);
int			createtok_double_lesser(t_lexer *lexer);
int			istok_whitespace(t_lexer *lexer);
int			createtok_whitespace(t_lexer *lexer);
int			istok_word(t_lexer *lexer);
int			createtok_word(t_lexer *lexer);
int			istok_null(t_lexer *lexer);
int			createtok_null(t_lexer *lexer);

#endif

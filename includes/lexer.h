/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:02:19 by ntom              #+#    #+#             */
/*   Updated: 2019/11/25 16:24:32 by wbraeckm         ###   ########.fr       */
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

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:02:19 by ntom              #+#    #+#             */
/*   Updated: 2020/01/10 17:42:01 by wdaher-a         ###   ########.fr       */
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
** Enums
*/

enum		e_type
{
	T_NEWLINE,
	T_BRACEPARAM,
	T_DOUBLE_AMPERSAND,
	T_DOUBLE_PIPE,
	T_DOUBLE_LESSER,
	T_DOUBLE_GREATER,
	T_LESSER_AND,
	T_GREATER_AND,
	T_IO_NUMBER,
	T_LESSER,
	T_GREATER,
	T_PIPE,
	T_QUOTE,
	T_DOUBLE_QUOTE,
	T_SEMICOLON,
	T_AMPERSAND,
	T_WSPACE,
	T_WORD,
	T_NULL
};

enum		e_tmask
{
	M_NEWLINE = 1 << T_NEWLINE,
	M_BRACEPARAM = 1 << T_BRACEPARAM,
	M_DOUBLE_AMPERSAND = 1 << T_DOUBLE_AMPERSAND,
	M_DOUBLE_PIPE = 1 << T_DOUBLE_PIPE,
	M_DOUBLE_LESSER = 1 << T_DOUBLE_LESSER,
	M_DOUBLE_GREATER = 1 << T_DOUBLE_GREATER,
	M_LESSER_AND = 1 << T_LESSER_AND,
	M_GREATER_AND = 1 << T_GREATER_AND,
	M_IO_NUMBER = 1 << T_IO_NUMBER,
	M_LESSER = 1 << T_LESSER,
	M_GREATER = 1 << T_GREATER,
	M_PIPE = 1 << T_PIPE,
	M_QUOTE = 1 << T_QUOTE,
	M_DOUBLE_QUOTE = 1 << T_DOUBLE_QUOTE,
	M_SEMICOLON = 1 << T_SEMICOLON,
	M_AMPERSAND = 1 << T_AMPERSAND,
	M_WSPACE = 1 << T_WSPACE,
	M_WORD = 1 << T_WORD,
	M_NULL = 1 << T_NULL,
	M_ANY = ~0
};

/*
** Typedefs
*/

typedef struct s_token	t_token;
typedef struct s_hdoc	t_hdoc;
typedef struct s_io_nb	t_io_nb;
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

struct		s_hdoc
{
	t_token	token;
	char	*name;
	int		pipe[2];
	int		completed;
};

struct		s_io_nb
{
	t_token	token;
	int		io_nb;
};

struct		s_lexer
{
	t_vec	tokens; //NOTE: Do we really need this?
	char	*line;
	size_t	line_size;
	size_t	i;
	t_vec	stack;
	int		parse_error;
};

struct		s_tdef
{
	t_type	type;
	int		(*is_tok)(t_lexer *, t_token *);
	int		(*transform)(t_lexer *, t_token *);
};

/*
** Tokenization
*/

int			lexer(char *line, t_lexer *lex, t_sh *shell);
int			init_lexer(t_lexer *lexer, char *line);
int			tokenization(t_lexer *lexer, t_sh *shell);
void		token_free(t_token *token);
int			token_process(t_lexer *lexer, t_token *token);

/*
** Delimit
*/

int			delimit_token(t_lexer *lex, char **result);

/*
** Utils
*/

void		lexer_free(t_lexer *lexer);
int			stack_push(t_lexer *lex, t_type type);
t_type		stack_pop(t_lexer *lex);
t_type		stack_top(t_lexer *lex);
int			is_escaped(t_lexer *lex, size_t len);
int			handle_specials(t_lexer *lex, size_t len);
int			new_line_check(t_lexer *lex, size_t len);
int			make_stack_prompt(t_vec *stack, char **result);

/*
** Tokens
*/

int			istok_ampersand(t_lexer *lexer, t_token *token);
int			transform_ampersand(t_lexer *lexer, t_token *token);
int			istok_double_ampersand(t_lexer *lexer, t_token *token);
int			transform_double_ampersand(t_lexer *lexer, t_token *token);
int			istok_double_pipe(t_lexer *lexer, t_token *token);
int			transform_double_pipe(t_lexer *lexer, t_token *token);
int			istok_greater(t_lexer *lexer, t_token *token);
int			transform_greater(t_lexer *lexer, t_token *token);
int			istok_greaterand(t_lexer *lexer, t_token *token);
int			transform_greaterand(t_lexer *lexer, t_token *token);
int			istok_io_number(t_lexer *lexer, t_token *token);
int			transform_io_number(t_lexer *lexer, t_token *token);
int			istok_lesser(t_lexer *lexer, t_token *token);
int			transform_lesser(t_lexer *lexer, t_token *token);
int			istok_lesserand(t_lexer *lexer, t_token *token);
int			istok_pipe(t_lexer *lexer, t_token *token);
int			transform_pipe(t_lexer *lexer, t_token *token);
int			transform_lesserand(t_lexer *lexer, t_token *token);
int			istok_semicolon(t_lexer *lexer, t_token *token);
int			transform_semicolon(t_lexer *lexer, t_token *token);
int			istok_newline(t_lexer *lexer, t_token *token);
int			transform_newline(t_lexer *lexer, t_token *token);
int			istok_double_greater(t_lexer *lexer, t_token *token);
int			transform_double_greater(t_lexer *lexer, t_token *token);
int			istok_double_lesser(t_lexer *lexer, t_token *token);
int			transform_double_lesser(t_lexer *lexer, t_token *token);
int			istok_word(t_lexer *lexer, t_token *token);
int			transform_word(t_lexer *lexer, t_token *token);
int			istok_null(t_lexer *lexer, t_token *token);
int			transform_null(t_lexer *lexer, t_token *token);
int			resolve_alias(t_sh *shell, char *alias, char **return_val);
int			init_lexer(t_lexer *lexer, char *line);
int			replace_tilde(t_sh *shell, char **str);

#endif

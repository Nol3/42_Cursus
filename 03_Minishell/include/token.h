/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:32:31 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:32:34 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

enum e_token_type
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_token_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_token
{
	char				*content;
	int					len;
	enum e_token_type	type;
	enum e_token_state	state;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_token_list
{
	t_token	*first;
	t_token	*last;
	int		size;
}	t_token_list;

/*
-----------------------------
PARSE/TOKENS
-----------------------------
*/

//token_list_utils.c

/*
Checks if a token list is empty
*/
int				is_token_empty(t_token_list *list);
/*
Initializes the token list
*/
t_token_list	*init_token_list(t_token_list *list);
/*
Creates a new token from its arguments.
Returns a complete token if everything went ok,
returns NULL if any malloc failed
*/
t_token			*new_token(char *content, int len,
					enum e_token_type type, enum e_token_state state);
/*
Adds a token in the last position of the list
*/
void			add_token_last(t_token_list *list, t_token *new);
/*
Frees the whole list
*/
void			free_token_list(t_token_list *list);

//token_utils.c

/*
Returns 1 if char c is a special character, 0 if not
*/
int				in_charset(char c);
/*
Returns a pointer to a new string which is a duplicate of the string s,
but copies at most n bytes.
*/
char			*ft_strndup(char *s1, size_t n);

//aux_tokenize.c

/*
Adds a word token into the list
@return Length of the word added if correct, 0 if not
*/
int				tokenize_word(t_token_list *list, char *str,
					enum e_token_state state);

/*
Adds a quote token into the list
Can modify the state of the quotes
@param quote 1 if single quote, 2 if double quote
@return Length of the word added if correct, 0 if not
*/
int				tokenize_quote(t_token_list *list, char *str,
					enum e_token_state *state, int quote);

/*
If next character isn't special or isn't a '=',
adds an enviroment token into the list.
If not, it calls tokenize_word to add '$' as a word token
@return Length of the word added if correct, 0 if not
*/
int				tokenize_env(t_token_list *list, char *str,
					enum e_token_state state);

/*
Adds a redirection token into the list
@param quote 1 if single quote, 2 if double quote
@return Length of the word added if correct, 0 if not
*/
int				tokenize_redir(t_token_list *list, char *str,
					enum e_token_state state);

#endif
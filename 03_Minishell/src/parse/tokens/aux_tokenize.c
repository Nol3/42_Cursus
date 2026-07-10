/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:36:39 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:36:40 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	tokenize_word(t_token_list *list, char *str, enum e_token_state state)
{
	t_token	*token;
	int		i;

	i = 0;
	while (!in_charset(str[i]))
		i++;
	token = new_token(str, i, WORD, state);
	if (!token)
		return (0);
	add_token_last(list, token);
	return (i);
}

int	tokenize_quote(t_token_list *list, char *str,
					enum e_token_state *state, int quote)
{
	t_token				*token;
	enum e_token_state	state_quote;
	enum e_token_type	type_quote;

	state_quote = IN_QUOTE;
	type_quote = QUOTE;
	if (quote == 2)
	{
		state_quote = IN_DQUOTE;
		type_quote = DOUBLE_QUOTE;
	}
	if (*state == GENERAL)
	{
		token = new_token(str, 1, type_quote, *state);
		*state = state_quote;
	}
	else
	{
		if (*state == state_quote)
			*state = GENERAL;
		token = new_token(str, 1, type_quote, *state);
	}
	if (!token)
		return (0);
	return (add_token_last(list, token), 1);
}

int	tokenize_env(t_token_list *list, char *str, enum e_token_state state)
{
	t_token	*token;
	int		i;

	i = 1;
	if (in_charset(str[i]) || str[i] == '=')
	{
		token = new_token("$", i, WORD, state);
		if (!token)
			return (0);
	}
	else
	{
		if (str[i] == '?')
			i++;
		else
			while ((ft_isalnum(str[i]) && ft_isalpha(str[1]))
				|| (ft_isdigit(str[i]) && ft_isdigit(str[1])))
				i++;
		token = new_token(str, i, ENV, state);
		if (!token)
			return (0);
	}
	add_token_last(list, token);
	return (i);
}

int	tokenize_redir(t_token_list *list, char *str, enum e_token_state state)
{
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
			token = new_token(str, ++i, HERE_DOC, state);
		else
			token = new_token(str, i, REDIR_IN, state);
	}
	else if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			token = new_token(str, ++i, DREDIR_OUT, state);
		else
			token = new_token(str, i, REDIR_OUT, state);
	}
	if (!token)
		return (0);
	add_token_last(list, token);
	return (i);
}

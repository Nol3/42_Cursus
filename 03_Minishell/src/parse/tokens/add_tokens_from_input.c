/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens_from_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:36:34 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:36:35 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
static void	print_node(t_token *token)
{
	int	i;

	i = 0;
	printf("content: ");
	while (i < token->len)
		putchar(token->content[i++]);
	printf(", len: %i", token->len);
	printf(", state: %i", token->state);
	printf(", token: %i\n", token->type);
}

static void	print_list(t_token_list *list)
{
	t_token	*token;

	token = list->first;
	while (token)
	{
		print_node(token);
		token = token->next;
	}
}
*/

static int	tokenize_pipe(t_token_list *list, enum e_token_state state)
{
	t_token	*token;

	token = new_token("|", 1, PIPE_LINE, state);
	if (!token)
		return (0);
	add_token_last(list, token);
	return (1);
}

static int	tokenize_space(t_token_list *list, enum e_token_state state)
{
	t_token	*token;

	token = new_token(" ", 1, WHITE_SPACE, state);
	if (!token)
		return (0);
	add_token_last(list, token);
	return (1);
}

static int	tokenize(t_token_list *list, char *input, int i,
				enum e_token_state *state)
{
	if (!in_charset(input[i]))
		return (i + tokenize_word(list, input + i, *state));
	if (input[i] == '\'')
		return (i + tokenize_quote(list, input + i, state, 1));
	if (input[i] == '\"')
		return (i + tokenize_quote(list, input + i, state, 2));
	if (input[i] == '$')
		return (i + tokenize_env(list, input + i, *state));
	if (input[i] == '<' || input[i] == '>')
		return (i + tokenize_redir(list, input + i, *state));
	if (input[i] == '|')
		return (i + tokenize_pipe(list, *state));
	if (ft_isspace(input[i]))
		return (i + tokenize_space(list, *state));
	return (i);
}

int	add_tokens_from_input(t_data *data, char *input)
{
	int					i;
	int					j;
	enum e_token_state	state;

	data->token_list = NULL;
	data->token_list = init_token_list(data->token_list);
	if (!data->token_list)
		return (0);
	i = 0;
	state = GENERAL;
	while (input[i])
	{
		j = tokenize(data->token_list, input, i, &state);
		if (i == j)
			return (free_token_list(data->token_list), 0);
		i = j;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:36:46 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:36:47 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_token_empty(t_token_list *list)
{
	return (list->first == NULL);
}

t_token_list	*init_token_list(t_token_list *list)
{
	list = (t_token_list *)ft_calloc(sizeof(t_token_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_token	*new_token(char *content, int len,
						enum e_token_type type, enum e_token_state state)
{
	t_token	*new;
	char	*copy;

	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	copy = ft_strndup(content, len);
	if (!copy)
		return (free(new), NULL);
	new->content = copy;
	new->len = len;
	new->type = type;
	new->state = state;
	return (new);
}

void	add_token_last(t_token_list *list, t_token *new)
{
	if (is_token_empty(list))
		list->first = new;
	else
	{
		list->last->next = new;
		new->prev = list->last;
	}
	list->last = new;
	list->size++;
}

void	free_token_list(t_token_list *list)
{
	t_token	*current;
	t_token	*to_delete;

	if (!list)
		return ;
	current = list->first;
	while (current)
	{
		to_delete = current;
		current = current->next;
		free(to_delete->content);
		free(to_delete);
	}
	free(list);
}

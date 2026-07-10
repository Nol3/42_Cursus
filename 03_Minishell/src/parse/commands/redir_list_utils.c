/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:35:46 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:35:47 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_redir_empty(t_redir_list *list)
{
	return (list->first == NULL);
}

t_redir_list	*init_redir_list(t_redir_list *list)
{
	list = (t_redir_list *)ft_calloc(sizeof(t_redir_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_redir	*new_redir(char *file, enum e_token_type type)
{
	t_redir	*new;

	new = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	if (!new)
		return (NULL);
	new->file = file;
	new->type = type;
	return (new);
}

void	add_redir_last(t_redir_list *list, t_redir *new)
{
	if (!new)
		return ;
	if (is_redir_empty(list))
		list->first = new;
	else
	{
		list->last->next = new;
		new->prev = list->last;
	}
	list->last = new;
	list->size++;
}

void	free_redir_list(t_redir_list *list)
{
	t_redir	*current;
	t_redir	*to_delete;

	if (!list)
		return ;
	current = list->first;
	while (current)
	{
		to_delete = current;
		current = current->next;
		free(to_delete->file);
		free(to_delete);
	}
	free(list);
}

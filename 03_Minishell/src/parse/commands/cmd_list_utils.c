/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:35:00 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:35:01 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_cmd_empty(t_cmd_list *list)
{
	return (list->first == NULL);
}

t_cmd_list	*init_cmd_list(t_cmd_list *list)
{
	list = (t_cmd_list *)ft_calloc(sizeof(t_cmd_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_cmd	*new_cmd(char **args, t_redir_list *redir_list,
				enum e_built_in built_in)
{
	t_cmd	*new;

	new = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->args = args;
	new->redir_list = redir_list;
	new->built_in = built_in;
	new->fd_in = STDIN;
	new->fd_out = STDOUT;
	return (new);
}

void	add_cmd_last(t_cmd_list *list, t_cmd *new)
{
	if (is_cmd_empty(list))
		list->first = new;
	else
	{
		list->last->next = new;
		new->prev = list->last;
	}
	list->last = new;
	list->size++;
}

void	free_cmd_list(t_cmd_list *list)
{
	t_cmd	*current;
	t_cmd	*to_delete;

	if (!list)
		return ;
	current = list->first;
	while (current)
	{
		to_delete = current;
		current = current->next;
		free_strs(to_delete->args);
		free_strs(to_delete->choosen_path);
		free_redir_list(to_delete->redir_list);
		free(to_delete);
	}
	free(list);
}

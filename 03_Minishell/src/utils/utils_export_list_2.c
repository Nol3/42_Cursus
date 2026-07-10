/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_list_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:34:01 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/22 16:34:02 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sub_export(t_export_list *current, t_export_list *new)
{
	if (!new->equal)
		return (free_export_list(new));
	if (current->value)
		free(current->value);
	current->value = ft_strdup(new->value);
	current->equal = new->equal;
	free_export_list(new);
	return ;
}

t_export_list	*add_export_sorted(t_export_list *current, t_export_list *new)
{
	t_export_list	*first;
	t_export_list	*previous;

	first = current;
	if (!first)
		return (new);
	previous = NULL;
	while (current
		&& ft_strncmp(new->key, current->key, ft_strlen(new->key) + 1) >= 0)
	{
		if (strs_are_equal(new->key, current->key))
			return (sub_export(current, new), first);
		previous = current;
		current = current->next;
	}
	if (previous)
		previous->next = new;
	else
		first = new;
	new->next = current;
	return (first);
}

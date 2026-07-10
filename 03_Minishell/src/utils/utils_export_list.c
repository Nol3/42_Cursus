/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:47:21 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/22 16:31:38 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export_list(t_data *data)
{
	t_export_list	*current;
	int				fd_out;

	if (!data || !data->export_list)
		return ;
	current = data->export_list;
	fd_out = STDOUT;
	if (data->current_cmd)
		fd_out = data->current_cmd->fd_out;
	while (current)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(current->key, fd_out);
		if (current->equal)
		{
			ft_putstr_fd("=\"", fd_out);
			ft_putstr_fd(current->value, fd_out);
			ft_putstr_fd("\"", fd_out);
		}
		ft_putstr_fd("\n", fd_out);
		current = current->next;
	}
}

t_export_list	*get_export_list_node(char *str)
{
	t_export_list	*new;
	char			*delimiter;

	new = (t_export_list *)ft_calloc(1, sizeof(t_export_list));
	if (!new)
		return (NULL);
	delimiter = ft_strchr(str, '=');
	if (!delimiter)
	{
		new->key = ft_strdup(str);
		if (!new->key)
			return (free(new), NULL);
		return (new);
	}
	new->equal = 1;
	new->key = ft_substr(str, 0, delimiter - str);
	if (!new->key)
		return (free(new), NULL);
	new->value = ft_strdup(delimiter + 1);
	if (!new->value)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

t_export_list	*get_export_list(char **envp)
{
	t_export_list	*first;
	t_export_list	*new;
	int				i;

	first = NULL;
	i = -1;
	while (envp[++i])
	{
		new = get_export_list_node(envp[i]);
		if (!new)
			return (free_export_list(first), NULL);
		first = add_export_sorted(first, new);
	}
	return (first);
}

void	free_export_list(t_export_list *current)
{
	t_export_list	*to_delete;

	to_delete = NULL;
	while (current)
	{
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		to_delete = current;
		current = current->next;
		free(to_delete);
	}
}

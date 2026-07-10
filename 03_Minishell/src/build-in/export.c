/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:33:28 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/23 16:12:07 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_envp_list(t_envp_list *list)
{
	t_envp_list	*current;
	t_envp_list	*to_delete;

	current = list;
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

static t_envp_list	*get_envp_list_node(char *str)
{
	t_envp_list	*new;
	char		*delimiter;

	new = (t_envp_list *)malloc(sizeof(t_envp_list));
	if (!new)
		return (NULL);
	delimiter = ft_strchr(str, '=');
	if (!delimiter)
		return (free(new), NULL);
	new->key = ft_substr(str, 0, delimiter - str);
	if (!new->key)
		return (free(new), NULL);
	if (!ft_strlen(new->key))
		return (free(new->key), free(new), print_error("Key not found"), NULL);
	new->value = ft_strdup(delimiter + 1);
	if (!new->value)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

static t_envp_list	*export_variable(t_envp_list *current, t_envp_list *new)
{
	t_envp_list	*first;
	t_envp_list	*previous;

	first = current;
	previous = NULL;
	while (current)
	{
		if (strs_are_equal(new->key, current->key))
		{
			free(current->value);
			current->value = ft_strdup(new->value);
			free_envp_list(new);
			return (first);
		}
		previous = current;
		current = current->next;
	}
	if (previous)
		previous->next = new;
	else
		first = new;
	return (first);
}

int	is_key_valid(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '_' && (str[1] == '\0' || str[1] == '='))
		return (0);
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (print_error("export: not a valid identifier"));
	while (str && str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (print_error("export: not a valid identifier"));
		i++;
	}
	return (1);
}

int	ft_export(t_data *data)
{
	int				i;
	t_envp_list		*new_envp;
	t_export_list	*new_export;

	i = 0;
	if (!data->current_cmd->args[1])
		return (print_export_list(data), EXIT_SUCCESS);
	while (data->current_cmd->args[++i])
	{
		if (!is_key_valid(data->current_cmd->args[i]))
			continue ;
		new_envp = get_envp_list_node(data->current_cmd->args[i]);
		if (new_envp)
			data->envp_list = export_variable(data->envp_list, new_envp);
		new_export = get_export_list_node(data->current_cmd->args[i]);
		if (new_export)
			data->export_list = add_export_sorted(data->export_list,
					new_export);
	}
	data->status = 0;
	update_envp(data);
	return (EXIT_SUCCESS);
}

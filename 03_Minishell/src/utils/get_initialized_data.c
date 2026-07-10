/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_initialized_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:37:26 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/22 10:30:48 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	new->value = ft_strdup(delimiter + 1);
	if (!new->value)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

static t_envp_list	*get_envp_list(char **envp)
{
	t_envp_list	*first;
	t_envp_list	*current;
	t_envp_list	*previous;
	int			i;

	first = NULL;
	current = NULL;
	previous = NULL;
	i = -1;
	while (envp[++i])
	{
		current = get_envp_list_node(envp[i]);
		if (!current)
			return (NULL);
		if (!previous)
			first = current;
		if (previous)
			previous->next = current;
		previous = current;
	}
	return (first);
}

static char	**get_envp(char **envp)
{
	char	**tmp;
	char	**new;
	int		count;
	int		i;

	count = 0;
	tmp = envp;
	while (*tmp)
	{
		count++;
		tmp++;
	}
	new = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < count)
		new[i] = ft_strdup(envp[i]);
	new[i] = NULL;
	return (new);
}

static int	initialize_built_in_cmd(t_data *data)
{
	data->built_in_cmd[0] = ft_strdup("echo");
	if (!data->built_in_cmd[0])
		return (0);
	data->built_in_cmd[1] = ft_strdup("cd");
	if (!data->built_in_cmd[1])
		return (0);
	data->built_in_cmd[2] = ft_strdup("pwd");
	if (!data->built_in_cmd[2])
		return (0);
	data->built_in_cmd[3] = ft_strdup("export");
	if (!data->built_in_cmd[3])
		return (0);
	data->built_in_cmd[4] = ft_strdup("unset");
	if (!data->built_in_cmd[4])
		return (0);
	data->built_in_cmd[5] = ft_strdup("env");
	if (!data->built_in_cmd[5])
		return (0);
	data->built_in_cmd[6] = ft_strdup("exit");
	if (!data->built_in_cmd[6])
		return (0);
	data->built_in_cmd[7] = NULL;
	return (1);
}

t_data	*get_initialized_data(char **envp)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (print_error("Malloc failed"), NULL);
	if (!initialize_built_in_cmd(data))
		return (print_error("Initializing built in cmd failed"), NULL);
	data->envp = get_envp(envp);
	if (!data->envp)
		return (print_error("Duping envp failed"), NULL);
	data->envp_list = get_envp_list(data->envp);
	if (!data->envp_list)
		return (print_error("Creating envp_list failed"), NULL);
	data->export_list = get_export_list(data->envp);
	if (!data->export_list)
		return (print_error("Creating export_list failed"), NULL);
	return (data);
}

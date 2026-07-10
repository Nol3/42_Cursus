/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:37:23 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/22 10:21:11 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_envp_list(t_data *data)
{
	t_envp_list	*current;
	t_envp_list	*to_delete;

	current = data->envp_list;
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

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (data->built_in_cmd[i])
			free(data->built_in_cmd[i]);
	}
	if (data->envp)
		free_strs(data->envp);
	free_envp_list(data);
	free_export_list(data->export_list);
	if (data->token_list)
		free_token_list(data->token_list);
	if (data->cmd_list)
		free_cmd_list(data->cmd_list);
	free(data);
}

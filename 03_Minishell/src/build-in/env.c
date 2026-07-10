/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:31:17 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/21 16:31:18 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	t_envp_list	*current;

	current = data->envp_list;
	while (current)
	{
		ft_putstr_fd(current->key, data->current_cmd->fd_out);
		ft_putstr_fd("=", data->current_cmd->fd_out);
		ft_putstr_fd(current->value, data->current_cmd->fd_out);
		ft_putstr_fd("\n", data->current_cmd->fd_out);
		current = current->next;
	}
}

int	env(t_data *data)
{
	if (data->current_cmd->args[1])
	{
		print_error("env: Too many arguments");
		return (1);
	}
	else if (ft_strncmp(data->current_cmd->args[0], "env", 3) == 0
		&& data->current_cmd->args[0][3] == '\0')
		ft_env(data);
	else
	{
		print_error("Bad command");
		return (1);
	}
	return (0);
}

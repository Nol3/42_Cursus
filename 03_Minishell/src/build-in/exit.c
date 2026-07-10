/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:33:17 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/23 17:13:08 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_is_a_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_exit_code(t_data *data)
{
	if (!data->current_cmd->args[1])
		return (0);
	if (str_is_a_nbr(data->current_cmd->args[1]))
		return (ft_atoi(data->current_cmd->args[1]) % 256);
	print_error("exit: numeric argument required");
	return (255);
}

int	ft_exit(t_data *data)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (data->current_cmd->args[1] && data->current_cmd->args[2])
	{
		print_error("exit: too many arguments");
		return (EXIT_FAILURE);
	}
	data->exit = 1;
	return (get_exit_code(data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:31:14 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/22 16:50:49 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_a_not_nl_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] != '-')
		return (0);
	while (str && str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

static int	not_new_line(char **strs)
{
	int	i;

	i = 1;
	while (strs[i] && is_a_not_nl_flag(strs[i]))
		i++;
	return (i - 1);
}

static int	ft_echo(t_data *data)
{
	int		i;
	int		not_nl;

	i = 1;
	not_nl = not_new_line(data->current_cmd->args);
	if (!data->current_cmd->args[1])
	{
		ft_putstr_fd("\n", data->current_cmd->fd_out);
		return (EXIT_SUCCESS);
	}
	if (not_nl != 0 && !data->current_cmd->args[i + not_nl])
		return (EXIT_SUCCESS);
	i += not_nl;
	while (data->current_cmd->args[i])
	{
		ft_putstr_fd(data->current_cmd->args[i], data->current_cmd->fd_out);
		if (data->current_cmd->args[++i])
			ft_putstr_fd(" ", data->current_cmd->fd_out);
	}
	if (not_nl == 0)
		ft_putstr_fd("\n", data->current_cmd->fd_out);
	return (EXIT_SUCCESS);
}

int	echo(t_data *data)
{
	if (ft_strncmp(data->current_cmd->args[0], "echo", 4) == 0
		&& data->current_cmd->args[0][4] == '\0')
	{
		return (ft_echo(data));
	}
	else
		return (EXIT_SUCCESS);
}

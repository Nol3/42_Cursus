/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_initialization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:34:14 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 19:53:47 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_for_new_read(t_data *data)
{
	if (data->token_list)
	{
		free_token_list(data->token_list);
		data->token_list = NULL;
	}
	if (data->cmd_list)
	{
		free_cmd_list(data->cmd_list);
		data->cmd_list = NULL;
	}
}

void	console_initialization(t_data *data)
{
	char	*input;

	while (data->exit != 1)
	{
		input = readline("Minishell$ ");
		if (!input)
		{
			data->exit = 1;
			continue ;
		}
		if (add_tokens_from_input(data, input)
			&& valid_token_list(data->token_list)
			&& add_commands_from_input(data)
			&& handle_redirections(data))
		{
			ft_pipex(data);
			if (*input != '\0')
				add_history(input);
		}
		free(input);
		free_for_new_read(data);
	}
}

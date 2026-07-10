/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_commands_from_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:34:25 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:34:40 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
static void	print_redir(t_redir *redir)
{
	if (!redir)
		return ;
	printf("%i, %s\n", redir->type, redir->file);
}

static void	print_redir_list(t_redir_list *redir_list)
{
	t_redir	*redir;

	if (!redir_list)
		return ;
	redir = redir_list->first;
	while (redir)
	{
		print_redir(redir);
		redir = redir->next;
	}
}

static void	print_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd || !(cmd->args))
		return ;
	i = -1;
	while (cmd->args[++i])
	{
		printf("Arg %i: %s\n", i, cmd->args[i]);
	}
	print_redir_list(cmd->redir_list);
}

static void	print_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->first;
	while (cmd)
	{
		print_cmd(cmd);
		cmd = cmd->next;
	}
}
*/

static t_token	*add_command_to_list(t_cmd_list *cmd_list, t_token *current,
									int args_size, t_data *data)
{
	char			**args;
	t_redir_list	*redir_list;
	enum e_built_in	built_in;
	t_cmd			*cmd;

	args = (char **)ft_calloc(sizeof(char *), args_size + 2);
	if (!args)
		return (NULL);
	redir_list = NULL;
	redir_list = init_redir_list(redir_list);
	if (!redir_list)
		return (free(args), NULL);
	get_lists(&current, data, args, redir_list);
	if (!args || !redir_list)
		return (free_strs(args), free_redir_list(redir_list), NULL);
	built_in = get_built_in(args[0]);
	cmd = new_cmd(args, redir_list, built_in);
	if (!cmd)
		return (free_strs(args), free_redir_list(redir_list), NULL);
	add_cmd_last(cmd_list, cmd);
	return (current);
}

int	add_commands_from_input(t_data *data)
{
	t_token	*current;
	t_token	*updated;

	if (is_token_empty(data->token_list))
		return (0);
	current = data->token_list->first;
	data->cmd_list = init_cmd_list(data->cmd_list);
	if (!data->cmd_list)
		return (0);
	while (current)
	{
		if (current->type == PIPE_LINE)
			current = current->next;
		updated = add_command_to_list(data->cmd_list, current,
				data->token_list->size, data);
		if (updated == current)
			return (0);
		current = updated;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:42 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/26 18:41:00 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			g_pack;

int	ft_pipex(t_data *data)
{
	int	status;
	int	cmd_count;

	data->current_cmd = data->cmd_list->first;
	status = 0;
	cmd_count = 0;
	if (data->cmd_list->size > 1)
		cmd_count = 1;
	while (data->current_cmd)
	{
		if (data->current_cmd->built_in != NOT_BUILT_IN)
			status = ft_exec_builtin(data);
		else
			status = ft_exec_cmd(data, cmd_count);
		g_pack = 0;
		data->status = status;
		data->current_cmd = data->current_cmd->next;
		cmd_count++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_cmd(t_data *data, int cmd_count)
{
	g_pack = 1;
	return (ft_fork(data, cmd_count));
}

static void	child_process_redir(t_cmd *node)
{
	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
}

static char	*resolve_absolute_path(char *cmd, char **envp)
{
	char	**envp_paths;
	char	*absolute_path;

	if (cmd[0] == '/')
		return (strdup(cmd));
	envp_paths = get_paths(envp);
	absolute_path = abs_bin_path(cmd, envp_paths);
	ft_free_matrix(envp_paths);
	return (absolute_path);
}

int	ft_child_process(t_data *data)
{
	int		original_stdin;
	int		original_stdout;
	char	*absolute_path;
	int		exit_status;

	exit_status = 0;
	original_stdin = data->current_cmd->fd_in;
	original_stdout = data->current_cmd->fd_out;
	if (data->current_cmd->args[0] == NULL)
		return (data->status);
	absolute_path = resolve_absolute_path(data->current_cmd->args[0],
			data->envp);
	if (!absolute_path)
		return (127);
	child_process_redir(data->current_cmd);
	data->status = execve(absolute_path, data->current_cmd->args, data->envp);
	if (data->status < 0)
	{
		free(absolute_path);
		data->status = 127;
		ft_redir_fd_std(original_stdin, exit_status, original_stdout);
	}
	return (data->status);
}

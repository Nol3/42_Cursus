/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:50 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/23 17:07:04 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir_fd_std(int fd, int std, int fd2)
{
	if (fd != UNDEF_FD && fd != std)
	{
		if (dup2(fd2, std) < 0)
			print_error("REDIR_ERROR");
		close(fd);
	}
}

int	ft_exec_builtin(t_data *data)
{
	int	exit;

	exit = 0;
	if (data->current_cmd->built_in == B_ECHO)
		exit = echo(data);
	else if (data->current_cmd->built_in == B_CD)
		exit = cd(data);
	else if (data->current_cmd->built_in == B_PWD)
		exit = ft_pwd(data);
	else if (data->current_cmd->built_in == B_EXPORT)
		exit = ft_export(data);
	else if (data->current_cmd->built_in == B_UNSET)
		exit = ft_unset(data);
	else if (data->current_cmd->built_in == B_ENV)
		exit = env(data);
	else if (data->current_cmd->built_in == B_EXIT)
		exit = ft_exit(data);
	else
		return (EXIT_FAILURE);
	return (exit);
}

static void	handle_child_process(t_data *data)
{
	data->status = ft_child_process(data);
}

static void	handle_parent_process(t_data *data, pid_t id, int *status)
{
	waitpid(id, status, 0);
	if (data->current_cmd->fd_in != UNDEF_FD
		&& data->current_cmd->fd_in != STDIN)
		close(data->current_cmd->fd_in);
	if (data->current_cmd->fd_out != UNDEF_FD
		&& data->current_cmd->fd_out != STDOUT)
		close(data->current_cmd->fd_out);
}

int	ft_fork(t_data *data, int cmd_count)
{
	int		status;
	pid_t	id;

	(void)cmd_count;
	status = UNDEF_FD;
	id = fork();
	if (id == 0)
		handle_child_process(data);
	else if (id > 0)
		handle_parent_process(data, id, &status);
	else
	{
		perror("fork");
		status = EXIT_FAILURE;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (data->status);
}

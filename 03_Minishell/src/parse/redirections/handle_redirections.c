/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:36:29 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/26 18:39:57 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	handle_pipe(t_cmd *cmd, int *fd_in)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (print_error("Pipe error"), 0);
	if (cmd->fd_out > 2)
		close(fd[1]);
	else
		cmd->fd_out = fd[1];
	*fd_in = fd[0];
	return (1);
}

static int	handle_redir_list(t_data *data, t_cmd *cmd, int *fd_in)
{
	int		ok;
	t_redir	*redir;

	if (*fd_in != 0)
	{
		cmd->fd_in = *fd_in;
		*fd_in = STDIN;
	}
	if (!cmd->redir_list || is_redir_empty(cmd->redir_list))
		return (1);
	redir = cmd->redir_list->first;
	ok = 1;
	while (redir && ok)
	{
		ok = handle_redir(data, cmd, redir);
		redir = redir->next;
	}
	return (1);
}

int	handle_redirections(t_data *data)
{
	int		fd_in;
	int		ok;
	t_cmd	*cmd;

	if (!data || !data->cmd_list || is_cmd_empty(data->cmd_list))
		return (0);
	cmd = data->cmd_list->first;
	fd_in = STDIN;
	ok = 1;
	while (cmd && ok)
	{
		ok = handle_redir_list(data, cmd, &fd_in);
		if (ok && cmd && cmd->next)
			ok = handle_pipe(cmd, &fd_in);
		cmd = cmd->next;
	}
	return (1);
}

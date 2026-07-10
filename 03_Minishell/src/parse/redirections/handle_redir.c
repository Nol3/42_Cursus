/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:36:26 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/26 18:40:10 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	redir_in(t_cmd *cmd, t_redir *redir)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = open(redir->file, O_RDONLY);
	if (cmd->fd_in == -1)
		return (print_error("When opening file"), 0);
	return (1);
}

static int	redir_out(t_cmd *cmd, t_redir *redir)
{
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (redir->type == REDIR_OUT)
		cmd->fd_out = open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		cmd->fd_out = open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (cmd->fd_out == -1)
		return (0);
	return (1);
}

int	handle_redir(t_data *data, t_cmd *cmd, t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (redir_in(cmd, redir));
	if (redir->type == REDIR_OUT
		|| redir->type == DREDIR_OUT)
		return (redir_out(cmd, redir));
	else if (redir->type == HERE_DOC)
		return (here_doc(data, cmd, redir->file));
	return (1);
}

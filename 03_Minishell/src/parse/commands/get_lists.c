/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:35:42 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:35:43 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_redir	*get_redir(t_token **token, t_data *data)
{
	t_redir				*redir;
	enum e_token_type	type;
	char				*file;

	type = (*token)->type;
	if (!is_redir(type))
		return (NULL);
	*token = (*token)->next;
	file = get_arg(token, data);
	if (!file)
		return (NULL);
	if (file[0] == '\0')
		return (print_error("No such file or directory"), NULL);
	redir = new_redir(file, type);
	if (!redir)
		return (NULL);
	return (redir);
}

static int	modify_redir_list(t_token **token, t_data *data,
		t_redir_list *redir_list)
{
	t_redir	*redir;

	if ((*token) && is_redir((*token)->type))
	{
		redir = get_redir(token, data);
		if (!redir)
			return (0);
		add_redir_last(redir_list, redir);
	}
	return (1);
}

void	get_lists(t_token **token, t_data *data, char **args,
		t_redir_list *redir_list)
{
	int	i;

	if (token == NULL || data == NULL || args == NULL
		|| redir_list == NULL)
		return ;
	i = -1;
	while (*token && (*token)->type != PIPE_LINE)
	{
		if (*token && ((*token)->type == WHITE_SPACE))
			*token = skip_spaces(*token, 1);
		if ((*token) && (*token)->type != PIPE_LINE
			&& !is_redir((*token)->type))
		{
			args[++i] = get_arg(token, data);
			if (args[i] == NULL)
				return (free_strs(args), free_redir_list(redir_list));
			if (args[i][0] == '\0')
			{
				free(args[i]);
				args[i--] = NULL;
			}
		}
		if (!modify_redir_list(token, data, redir_list))
			return (free_strs(args), free_redir_list(redir_list));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:36:20 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:36:23 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_redir(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HERE_DOC || type == DREDIR_OUT);
}

t_token	*skip_spaces(t_token *token, int next)
{
	if (next)
		token = token->next;
	else
		token = token->prev;
	while (token && token->type == WHITE_SPACE)
	{
		if (next)
			token = token->next;
		else
			token = token->prev;
	}
	return (token);
}

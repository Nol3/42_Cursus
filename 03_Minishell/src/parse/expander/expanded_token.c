/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:35:56 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/21 16:35:57 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_value(char *key, t_data *data)
{
	t_envp_list	*list;

	if (strs_are_equal(key, "?"))
		return (ft_itoa(data->status));
	list = data->envp_list;
	while (list && !strs_are_equal(key, list->key))
		list = list->next;
	if (list)
		return (list->value);
	return ("");
}

char	*expanded_token(t_token *token, t_data *data)
{
	char		*value;
	char		*copy;

	if (token->type != ENV)
		return (NULL);
	value = get_value((token->content) + 1, data);
	copy = ft_strdup(value);
	if (strs_are_equal((token->content) + 1, "?"))
		free(value);
	if (!copy)
		return (NULL);
	return (copy);
}

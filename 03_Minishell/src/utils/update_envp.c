/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:37:35 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/22 10:38:32 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		printf("%s\n", strs[i]);
}

static int	envp_list_size(t_envp_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

static char	*get_string_from_envp(t_envp_list *list)
{
	int		size;
	char	*str;

	size = ft_strlen(list->key) + ft_strlen(list->value) + 2;
	str = (char *)ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, list->key, ft_strlen(list->key) + 1);
	ft_strlcat(str, "=", ft_strlen(list->key) + 2);
	ft_strlcat(str, list->value, size);
	return (str);
}

static char	**get_envp_from_list(t_envp_list *list)
{
	char	**envp;
	int		i;

	envp = (char **)ft_calloc(envp_list_size(list) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = -1;
	while (list)
	{
		envp[++i] = get_string_from_envp(list);
		if (!envp[i])
			return (free_strs(envp), NULL);
		list = list->next;
	}
	return (envp);
}

int	update_envp(t_data *data)
{
	if (!data || !data->envp || !data->envp_list)
		return (1);
	free_strs(data->envp);
	data->envp = get_envp_from_list(data->envp_list);
	if (!data->envp)
		return (print_error("Malloc error"), 0);
	return (1);
}

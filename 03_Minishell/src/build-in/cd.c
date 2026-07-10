/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:31:10 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/21 16:40:28 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_env(char *key, t_envp_list *current)
{
	char	*value;

	value = NULL;
	while (current)
	{
		if (strs_are_equal(key, current->key))
		{
			value = ft_strdup(current->value);
			return (value);
		}
		current = current->next;
	}
	if (!value)
		value = ft_strdup("");
	return (value);
}

static char	*ft_get_path(t_data *data)
{
	char	*path;
	char	*path_redir;

	path = malloc(sizeof(char) * 4096);
	path_redir = ft_get_env("OLDPWD", data->envp_list);
	if (!getcwd(path, 4096))
		free(path);
	if (strs_are_equal(data->current_cmd->args[1], "-"))
	{
		if (!path_redir)
			path_redir = ft_get_env("PWD", data->envp_list);
		free(path);
		return (path_redir);
	}
	if (!data->current_cmd->args[1])
		data->current_cmd->args[1] = ft_strdup("");
	path = data->current_cmd->args[1];
	return (path);
}

static void	ft_reasign(char *key, char *value, t_envp_list *current)
{
	while (current)
	{
		if (strs_are_equal(key, current->key))
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

static int	ft_cd(char *old_pwd, t_data *data)
{
	char	*path;
	char	*home;

	path = ft_get_path(data);
	if (!path || strs_are_equal(path, "") || strs_are_equal(path, "~"))
	{
		home = ft_get_env("HOME", data->envp_list);
		if (chdir(home) != 0)
			return (free(home), print_error("CD: HOME not set"), 1);
		free(home);
	}
	else if ((chdir(path) != 0))
	{
		return (print_error("CD: No such file or directory\n"), 1);
	}
	ft_reasign("OLDPWD", old_pwd, data->envp_list);
	getcwd(old_pwd, sizeof(old_pwd));
	ft_reasign("PWD", old_pwd, data->envp_list);
	return (EXIT_SUCCESS);
}

int	cd(t_data *data)
{
	char	current_path[4096];

	getcwd(current_path, sizeof(current_path));
	ft_cd(current_path, data);
	return (0);
}

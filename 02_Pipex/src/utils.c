/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:25:00 by alcarden          #+#    #+#             */
/*   Updated: 2023/10/25 20:18:33 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*path;
	int		i;
	char	*routes;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		routes = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(routes, cmd);
		free(routes);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (all_paths[i++])
		free(all_paths[i]);
	free(all_paths);
	return (0);
}

void	ft_error(void)
{
	perror("Pipex");
	exit(EXIT_FAILURE);
}

void	ft_execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = 0;
	cmd = ft_split(argv, ' ');
	path = ft_find_path(cmd[0], envp);
	execve(path, cmd, envp);
	if (!path)
	{
		while (cmd[i++])
			free(cmd[i]);
		free(cmd);
		ft_error();
	}
	ft_error();
}

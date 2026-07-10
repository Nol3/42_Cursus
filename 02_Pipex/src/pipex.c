/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:25:12 by alcarden          #+#    #+#             */
/*   Updated: 2023/10/25 20:24:10 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(char **argv, char **envp, int *fd)
{
	int		file_in;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
		ft_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);
	close(fd[0]);
	ft_execute(argv[2], envp);
}

void	ft_parent_process(char **argv, char **envp, int *fd)
{
	int		file_out;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	close(fd[1]);
	ft_execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid1 = fork();
		if (pid1 == -1)
			ft_error();
		if (pid1 == 0)
		{
			ft_child_process(argv, envp, fd);
		}
		waitpid(pid1, NULL, 0);
		ft_parent_process(argv, envp, fd);
	}
	else
	{
		ft_printf("Pipex_Error: Bad arguments\n", 2);
		ft_printf("Example: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}

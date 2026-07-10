/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:10:54 by alcarden          #+#    #+#             */
/*   Updated: 2023/05/25 21:34:48 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stack_refill(char *stack)
{
	int		i;
	int		j;
	char	*new_stack;

	i = 0;
	j = 0;
	while (stack[i] != '\n' && stack[i])
		i++;
	if (!stack[i])
	{
		free(stack);
		return (0);
	}
	new_stack = malloc(ft_strlen(stack) - i + 1);
	if (!new_stack)
		return (NULL);
	i++;
	while (stack[i])
		new_stack[j++] = stack[i++];
	new_stack[j] = '\0';
	free(stack);
	return (new_stack);
}

char	*ft_get_line(char *stack)
{
	int		i;
	char	*line;

	if (!stack[0])
		return (NULL);
	i = 0;
	while (stack[i] != '\n' && stack[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	i = 0;
	while (stack[i] != '\n' && stack[i])
	{
		line[i] = stack[i];
		i++;
	}
	if (stack[i] == '\n')
	{
		line[i] = stack[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*ft_read_file(char *stack, int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(stack, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stack), NULL);
		buffer[bytes_read] = '\0';
		stack = ft_strjoin(buffer, stack);
	}
	free(buffer);
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stack = ft_read_file(stack, fd);
	if (!stack)
		return (NULL);
	line = ft_get_line(stack);
	stack = ft_stack_refill(stack);
	return (line);
}

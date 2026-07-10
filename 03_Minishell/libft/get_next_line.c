/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:18:16 by angcampo          #+#    #+#             */
/*   Updated: 2024/07/07 19:57:03 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_save_line(int fd, char *save)
{
	char	*buffer;
	int		done;
	ssize_t	read_bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ft_memset_gnl(buffer, '\0', BUFFER_SIZE + 1);
	done = 0;
	while (!done)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		save = ft_strjoin_gnl(save, buffer);
		done = ((ft_pos_char_in_string_gnl(buffer, '\n') < BUFFER_SIZE)
				|| (read_bytes == 0));
	}
	free(buffer);
	return (save);
}

static char	*ft_get_result(char *save)
{
	char	*result;

	result = ft_substr_gnl(save, 0, ft_pos_char_in_string_gnl(save, '\n') + 1);
	return (result);
}

static char	*ft_update_save(char *save)
{
	char	*update;

	update = ft_substr_gnl(save, ft_pos_char_in_string_gnl(save, '\n') + 1,
			ft_pos_char_in_string_gnl(save, '\0'));
	free(save);
	return (update);
}

char	*ft_get_next_line(int fd)
{
	static char	*save;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_save_line(fd, save);
	if (!save)
		return (NULL);
	if (!*save)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	result = ft_get_result(save);
	save = ft_update_save(save);
	return (result);
}

/*
int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR\n");
		return (1);
	}
	while (printf("%s", get_next_line(fd)))
		;
	close(fd);
}
*/

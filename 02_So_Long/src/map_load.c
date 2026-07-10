/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:13:54 by alcarden          #+#    #+#             */
/*   Updated: 2024/02/03 14:11:28 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

char	*ft_read_map(char *file)
{
	int		fd;
	int		fsize;
	char	*buff;
	char	*file_read;

	fsize = 0;
	buff = malloc(sizeof(char) * 2);
	fd = open(file, O_RDONLY);
	while (read(fd, buff, 1) == 1)
		fsize++;
	free(buff);
	if (fsize == 0)
		perror("Empty map");
	close(fd);
	fd = open(file, O_RDONLY);
	file_read = malloc(sizeof(char) * fsize + 1);
	read(fd, file_read, fsize);
	file_read[fsize] = '\0';
	close(fd);
	return (file_read);
}

void	ft_load_map(char *file, t_element *element)
{
	char	*file_read;

	file_read = ft_read_map(file);
	element->full_map = ft_split(file_read, '\n');
	element->map_cpy = ft_split(file_read, '\n');
	free(file_read);
}

void	ft_get_height_width(t_element *element, char **map_load)
{
	int	i;
	int	j;

	i = 0;
	while (map_load[i])
	{
		j = 0;
		while (map_load[i][j])
			j++;
		i++;
	}
	element->height = i;
	element->width = j;
}

t_element	*ft_gen_map(mlx_t *mlx, t_element *element)
{
	int	i;
	int	j;

	i = 0;
	while (element->full_map[i])
	{
		j = 0;
		while (element->full_map[i][j])
		{
			if (element->full_map[i][j] == '1')
				ft_wall(mlx, i, j, element);
			else if (element->full_map[i][j] == 'X')
				ft_enemy(mlx, i, j, element);
			else if (element->full_map[i][j] == '0')
				ft_floor(mlx, i, j, element);
			else if (element->full_map[i][j] == 'C')
				ft_collectible(mlx, i, j, element);
			else if (element->full_map[i][j] == 'E')
				ft_exit(mlx, i, j, element);
			else if (element->full_map[i][j] == 'P')
				ft_valere(mlx, i, j, element);
			j++;
		}
		i++;
	}
	return (element);
}

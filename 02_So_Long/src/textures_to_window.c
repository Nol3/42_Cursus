/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_to_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 06:02:30 by alcarden          #+#    #+#             */
/*   Updated: 2024/02/02 17:46:02 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_valere(mlx_t *mlx, int height, int width, t_element *element)
{
	mlx_image_to_window(mlx, element->floor,
		width * 64, height * 64);
	mlx_image_to_window(mlx, element->player,
		width * 64, height * 64);
	ft_valere_idle(element);
	element->move_x = height;
	element->move_y = width;
}

void	ft_exit(mlx_t *mlx, int height, int width, t_element *element)
{
	mlx_image_to_window(mlx, element->floor,
		width * 64, height * 64);
	mlx_image_to_window(mlx, element->exit,
		width * 64, height * 64);
}

void	ft_enemy(mlx_t *mlx, int height, int width, t_element *element)
{
	mlx_image_to_window(mlx, element->floor,
		width * 64, height * 64);
	mlx_image_to_window(mlx, element->enemy,
		width * 64, height * 64);
}

void	ft_collectible(mlx_t *mlx, int height, int width, t_element *element)
{
	mlx_image_to_window(mlx, element->floor,
		width * 64, height * 64);
	mlx_image_to_window(mlx, element->chest,
		width * 64, height * 64);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_and_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:11:47 by alcarden          #+#    #+#             */
/*   Updated: 2024/01/14 17:46:13 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_wall(mlx_t *mlx, int height, int width, t_element *element)
{
	mlx_image_to_window(mlx, element->wall,
		width * 64, height * 64);
}

void	ft_floor(mlx_t *mlx, int height, int width, t_element *element)
{
	mlx_image_to_window(mlx, element->floor,
		width * 64, height * 64);
}

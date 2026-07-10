/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_to_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:57:21 by alcarden          #+#    #+#             */
/*   Updated: 2024/06/20 16:41:20 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_load_textures(t_element *element)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./textures/valere_idle/idle_0.png");
	element->player = mlx_texture_to_image(element->mlx, texture);
	mlx_delete_texture(texture);

	texture = mlx_load_png("./textures/traps_copy.png");
	element->enemy = mlx_texture_to_image(element->mlx, texture);
	mlx_delete_texture(texture);

	texture = mlx_load_png("./textures/floor.png");
	element->floor = mlx_texture_to_image(element->mlx, texture);
	mlx_delete_texture(texture);

	texture = mlx_load_png("./textures/wall.png");
	element->wall = mlx_texture_to_image(element->mlx, texture);
	mlx_delete_texture(texture);

	texture = mlx_load_png("./textures/exit.png");
	element->exit = mlx_texture_to_image(element->mlx, texture);
	mlx_delete_texture(texture);

	texture = mlx_load_png("./textures/chest.png");
	element->chest = mlx_texture_to_image(element->mlx, texture);
	mlx_delete_texture(texture);

	ft_valere_load(element);
}

// void	ft_load_textures(t_element *element)
// {
//     mlx_texture_t	*texture;

//     texture = mlx_load_png("./textures/valere_idle/idle_0.png");
//     if (!texture) {
//         perror("Error loading texture ./textures/valere_idle/idle_0.png");
//         exit(EXIT_FAILURE);
//     }
//     element->player = mlx_texture_to_image(element->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!element->player) {
//         perror("Error converting texture to image (player)");
//         exit(EXIT_FAILURE);
//     }

//     texture = mlx_load_png("./textures/traps_copy.png");
//     if (!texture) {
//         perror("Error loading texture ./textures/traps_copy.png");
//         exit(EXIT_FAILURE);
//     }
//     element->enemy = mlx_texture_to_image(element->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!element->enemy) {
//         perror("Error converting texture to image (enemy)");
//         exit(EXIT_FAILURE);
//     }

//     texture = mlx_load_png("./textures/floor.png");
//     if (!texture) {
//         perror("Error loading texture ./textures/floor.png");
//         exit(EXIT_FAILURE);
//     }
//     element->floor = mlx_texture_to_image(element->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!element->floor) {
//         perror("Error converting texture to image (floor)");
//         exit(EXIT_FAILURE);
//     }

//     texture = mlx_load_png("./textures/wall.png");
//     if (!texture) {
//         perror("Error loading texture ./textures/wall.png");
//         exit(EXIT_FAILURE);
//     }
//     element->wall = mlx_texture_to_image(element->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!element->wall) {
//         perror("Error converting texture to image (wall)");
//         exit(EXIT_FAILURE);
//     }

//     texture = mlx_load_png("./textures/exit.png");
//     if (!texture) {
//         perror("Error loading texture ./textures/exit.png");
//         exit(EXIT_FAILURE);
//     }
//     element->exit = mlx_texture_to_image(element->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!element->exit) {
//         perror("Error converting texture to image (exit)");
//         exit(EXIT_FAILURE);
//     }

//     texture = mlx_load_png("./textures/chest.png");
//     if (!texture) {
//         perror("Error loading texture ./textures/chest.png");
//         exit(EXIT_FAILURE);
//     }
//     element->chest = mlx_texture_to_image(element->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!element->chest) {
//         perror("Error converting texture to image (chest)");
//         exit(EXIT_FAILURE);
//     }

//     ft_valere_load(element);
// }
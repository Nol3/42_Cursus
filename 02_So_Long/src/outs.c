/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:17:32 by alcarden          #+#    #+#             */
/*   Updated: 2024/06/20 16:49:03 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* */
/* Free memory from images and close */

void	ft_free_game(t_element *element)
{
	mlx_delete_image(element->mlx, element->wall);
	mlx_delete_image(element->mlx, element->floor);
	mlx_delete_image(element->mlx, element->chest);
	mlx_delete_image(element->mlx, element->player);
	mlx_delete_image(element->mlx, element->exit);
	mlx_delete_image(element->mlx, element->enemy);
	mlx_delete_image(element->mlx, element->valere1);
	mlx_delete_image(element->mlx, element->valere2);
	mlx_delete_image(element->mlx, element->valere3);
	mlx_delete_image(element->mlx, element->phrase);
	mlx_delete_image(element->mlx, element->steps_img);
	free(element->full_map);
	free(element->map_cpy);
	if (element->mlx != NULL)
		mlx_close_window(element->mlx);
	free(element->mlx);
	exit(EXIT_SUCCESS);
}

/* */
/* Free memory from all full_map */

void	ft_free_full_map(t_element *element)
{
	int	i;

	i = 0;
	while (i < element->width)
	{
		free(element->full_map[i]);
		i++;
	}
	free(element->full_map);
	element->full_map = NULL;
}

// void ft_free_game(t_element *element)
// {
//     mlx_delete_image(element->mlx, element->wall);
//     mlx_delete_image(element->mlx, element->floor);
//     mlx_delete_image(element->mlx, element->chest);
//     mlx_delete_image(element->mlx, element->player);
//     mlx_delete_image(element->mlx, element->exit);
//     mlx_delete_image(element->mlx, element->enemy);
//     mlx_delete_image(element->mlx, element->valere1);
//     mlx_delete_image(element->mlx, element->valere2);
//     mlx_delete_image(element->mlx, element->valere3);
//     mlx_delete_image(element->mlx, element->phrase);
//     mlx_delete_image(element->mlx, element->steps_img);
//     if (element->full_map) ft_free_full_map(element);
//     if (element->map_cpy) free(element->map_cpy);
// 	if (element->mlx) free(element->mlx);
//     if (element->mlx) {
//         mlx_close_window(element->mlx);
//         mlx_terminate(element->mlx);
//     }
// }

// void ft_free_full_map(t_element *element)
// {
//     int i;

//     if (element->full_map) {
//         for (i = 0; i < element->height; i++) {
//             if (element->full_map[i]) {
//                 free(element->full_map[i]);
//             }
//         }
//         free(element->full_map);
//         element->full_map = NULL;
//     }
// }

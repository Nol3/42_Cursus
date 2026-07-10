/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 05:41:43 by alcarden          #+#    #+#             */
/*   Updated: 2024/06/19 20:50:21 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_create_window(t_element *element)
{
	element->mlx = mlx_init(element->width * 64, element->height * 64,
			"so_long", false);
	ft_load_textures(element);
	element = ft_gen_map(element->mlx, element);
	mlx_key_hook(element->mlx, (mlx_keyfunc)ft_movement, element);
	mlx_close_hook(element->mlx, ft_close_window, element);
	mlx_loop_hook(element->mlx, ft_valere_idle, element);
	mlx_loop(element->mlx);
	mlx_terminate(element->mlx);
	ft_free_game(element);
	ft_free_full_map(element);
	free(element->mlx);
	free(element);
	return (EXIT_SUCCESS);
}

void	ft_close_window(void *param)
{
	t_element *element = (t_element *)param;

	ft_free_game(element);
	ft_free_full_map(element);
	free(element);
	mlx_close_window(element->mlx);
}

mlx_image_t *ft_put_steps(t_element *element) {
    char *str;
    static int first = 0;

    // Convertir el número de pasos a string.
    str = ft_itoa(element->steps);

    // Si no es la primera vez, eliminar la imagen anterior para evitar leaks.
    if (first) {
        if (element->phrase) {
            mlx_delete_image(element->mlx, element->phrase);
        }
        if (element->steps_img) {
            mlx_delete_image(element->mlx, element->steps_img);
        }
    } else {
        first = 1; // Marcar la primera ejecución completada.
    }

    // Crear y mostrar la nueva imagen con el texto "steps: ".
    element->phrase = mlx_put_string(element->mlx, "steps: ", 0, 0);
    mlx_image_to_window(element->mlx, element->phrase, 0, 0);

    // Crear y mostrar la nueva imagen con el número de pasos.
    element->steps_img = mlx_put_string(element->mlx, str, 64, 0);
    mlx_image_to_window(element->mlx, element->steps_img, 64, 0);

    // Liberar el string creado por ft_itoa.
    free(str);

    return (element->steps_img);
}

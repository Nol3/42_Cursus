/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:21 by alcarden          #+#    #+#             */
/*   Updated: 2024/06/19 19:48:14 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*Que todos los bordes sean 1*/
void	ft_verify_map(char **map, t_element *element)
{
	int		i;
	int		x;

	i = -1;
	while (map[++i])
	{
		x = -1;
		while (map[i][++x])
		{
			if ((i == 0 || i == element->height - 1)
				|| (x == 0 || x == element->width - 1))
			{
				if (map[i][x] != '1')
				{
					ft_printf("Map is not closed");
					exit(EXIT_SUCCESS);
				}
			}
		}
	}
	ft_check_items(element);
	ft_verify_counts(element);
	ft_count_column(element);
	ft_verify_win(element);
}

/*Número de player, chest y exit.*/
void	ft_check_items(t_element *element)
{
	int	x;
	int	y;

	y = 0;
	while (element->full_map[y])
	{
		x = 0;
		while (element->full_map[y][x])
		{
			if (element->full_map[y][x] == 'P')
				element->count_player++;
			if (element->full_map[y][x] == 'C')
				element->max_chest++;
			if (element->full_map[y][x] == 'E')
				element->count_exit++;
			x++;
		}
		y++;
	}
}

/* */
/*Comprueba que tenga los mínimos*/

void	ft_verify_counts(t_element *element)
{
	if (element->count_player != 1 || element->count_exit != 1)
	{
		free(element);
		ft_printf("No hay jugador o salida\n");
		exit(EXIT_SUCCESS);
	}
	if (element->max_chest <= 0)
	{
		free(element);
		ft_printf("No hay cofres en el mapa\n");
		exit(EXIT_SUCCESS);
	}
}

/*Que todas las filas tengan las misma anchura (n. de columnas)*/
void	ft_count_column(t_element *element)
{
	int		count_line;
	int		tmp;
	int		i;

	element->width = 0;
	tmp = 0;
	i = 0;
	count_line = ft_strlen(element->full_map[0]);
	while (element->full_map[i])
	{
		tmp = ft_strlen(element->full_map[i]);
		if (count_line != tmp)
		{
			ft_free_full_map(element);
			perror("Column size error");
		}
		i++;
	}
	element->width = tmp;
}

void	ft_exit_game(t_element *element)
{
	ft_printf("\nTerminas con %d movimientos.", element->steps);
	ft_free_game(element);
	exit(EXIT_SUCCESS);
}

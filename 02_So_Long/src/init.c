/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:18:38 by alcarden          #+#    #+#             */
/*   Updated: 2024/06/19 18:58:45 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_init_elements(t_element *element)
{
	element->mlx = 0;
	element->wall = 0;
	element->floor = 0;
	element->chest = 0;
	element->player = 0;
	element->exit = 0;
	element->enemy = 0;
	element->width = 0;
	element->height = 0;
	element->full_map = 0;
	element->map_cpy = 0;
	element->player_pos_x = 0;
	element->player_pos_y = 0;
	element->chest_counter = 0;
	element->max_chest = 0;
	element->steps = 0;
	element->count_player = 0;
	element->count_exit = 0;
	element->move_x = 0;
	element->move_y = 0;
	element->idle_timer = 0;
	element->is_idle = 0;
	element->valere1 = 0;
	element->valere2 = 0;
	element->valere3 = 0;
	element->phrase = 0;
	element->steps = 0;
}

void	ft_validate_map(t_element *element)
{
	int	x;
	int	y;

	y = 0;
	while (element->full_map[y])
	{
		x = 0;
		while (element->full_map[y][x])
		{
			if (ft_strchr("PEC01X", element->full_map[y][x]) == NULL)
			{
				ft_free_game(element);
				perror("only P,E,C,0,1,X allowed in map");
			}
			x++;
		}
		y++;
	}
}

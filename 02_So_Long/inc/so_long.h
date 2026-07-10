/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:33:32 by alcarden          #+#    #+#             */
/*   Updated: 2024/06/19 21:45:50 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../include/inc/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>

typedef struct s_element
{
	mlx_t			*mlx;
	mlx_image_t		*player;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*exit;
	mlx_image_t		*enemy;
	mlx_image_t		*chest;
	mlx_image_t		*phrase;
	mlx_image_t		*steps_img;
	mlx_image_t		*valere1;
	mlx_image_t		*valere2;
	mlx_image_t		*valere3;
	int				player_pos_x;
	int				player_pos_y;
	int				move_x;
	int				move_y;
	int				max_chest;
	int				chest_counter;
	int				count_player;
	int				count_exit;
	int				steps;
	int				width;
	int				height;
	int				idle_timer;
	int				is_idle;
	char			**full_map;
	char			**map_cpy;
}	t_element;

//añadir mlx_image_t para el Idle de Valere
//(6 imagenes) y meterlos en el init.

//create.c
int				ft_create_window(t_element *element);
void			ft_close_window(void *param);
mlx_image_t		*ft_put_steps(t_element *element);

//init.c
void			ft_init_elements(t_element *elements);
void			ft_validate_map(t_element *element);

//map_check.c
int				ft_check_extension(const char *file_name);

//map_load.c
char			*ft_read_map(char *file);
void			ft_load_map(char *file, t_element *element);
void			ft_get_height_width(t_element *elements, char **map_load);
t_element		*ft_gen_map(mlx_t *mlx, t_element *element);

//move.c
void			ft_movement(mlx_key_data_t paramkey, t_element *element);
void			ft_movement_up(t_element *element);
void			ft_movement_down(t_element *element);
void			ft_movement_left(t_element *element);
void			ft_movement_right(t_element *element);

//outs.c
void			ft_free_game(t_element *element);
void			ft_free_full_map(t_element *element);

//png_to_textures.c
void			ft_load_textures(t_element *element);

//solve.c
void			ft_verify_win(t_element *element);
void			ft_player_position(t_element *element,
					int *pl_width, int *pl_height);
void			ft_to_fill(t_element *element,
					int player_pos_x, int player_pos_y);
void			flood_fill(t_element *element, int player_pos_x,
					int player_pos_y, int *trues);

//textures_to_window.c
void			ft_valere(mlx_t *mlx, int height,
					int width, t_element *element);
void			ft_exit(mlx_t *mlx, int height, int width, t_element *element);
void			ft_enemy(mlx_t *mlx, int height, int width, t_element *element);
void			ft_collectible(mlx_t *mlx, int height,
					int width, t_element *element);
void			ft_open_exit(t_element *element);

//valere_move.c
void			ft_valere_idle(void *param);
void			ft_valere_load(t_element *element);
void			ft_player_position_animation(t_element *element,
					int animation_state);
void			draw_character(t_element *element,
					int animation_state, int i, int j);

//validate.c
void			ft_verify_map(char **map, t_element *element);
void			ft_check_items(t_element *element);
void			ft_verify_counts(t_element *element);
void			ft_count_column(t_element *element);
void			ft_exit_game(t_element *element);

//wall_and_floor.c
void			ft_wall(mlx_t *mlx, int height, int width, t_element *element);
void			ft_floor(mlx_t *mlx, int height, int width, t_element *element);
#endif
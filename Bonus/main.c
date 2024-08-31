/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:29:16 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/30 01:10:38 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	moves_hook(t_main *main)
{
	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
		ft_close(main);
	if (mlx_is_key_down(main->mlx, MLX_KEY_W))
		ft_turn(main, TOP, 0, 0);
	if (mlx_is_key_down(main->mlx, MLX_KEY_S))
		ft_turn(main, BOTTOM, 0, 0);
	if (mlx_is_key_down(main->mlx, MLX_KEY_A))
		ft_turn(main, LEFT, 0, 0);
	if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		ft_turn(main, RIGHT, 0, 0);
	if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
		1 && (main->player_angle -= 2 * (M_PI / 180), main->ld = 1);
	if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		1 && (main->player_angle += 2 * (M_PI / 180), main->ld = 1);
}

void	vert_inter(t_main *main, int i, t_vars *v)
{
	v->xinter = floor(main->player_x / PIXEL_NBR) * PIXEL_NBR;
	if (main->rays[i].facing_right)
		v->xinter += PIXEL_NBR;
	v->yinter = main->player_y + (v->xinter
			- main->player_x) * tan(main->rays[i].angle);
	v->xstep = PIXEL_NBR;
	if (!main->rays[i].facing_right)
		v->xstep *= -1;
	v->ystep = PIXEL_NBR * tan(main->rays[i].angle);
	if (!main->rays[i].facing_down && v->ystep > 0)
		v->ystep *= -1;
	if (main->rays[i].facing_down && v->ystep < 0)
		v->ystep *= -1;
	v->next_v_x = v->xinter;
	v->next_v_y = v->yinter;
	look_for_v_wall(main, v, i);
}

void	hor_inter(t_main *main, int i, t_vars *v)
{
	v->yinter = floor(main->player_y / PIXEL_NBR) * PIXEL_NBR;
	if (main->rays[i].facing_down)
		v->yinter += PIXEL_NBR;
	v->xinter = main->player_x + (v->yinter - main->player_y)
		/ tan(main->rays[i].angle);
	v->ystep = PIXEL_NBR;
	if (!main->rays[i].facing_down)
		v->ystep *= -1;
	v->xstep = PIXEL_NBR / tan(main->rays[i].angle);
	if (!main->rays[i].facing_right && v->xstep > 0)
		v->xstep *= -1;
	if (main->rays[i].facing_right && v->xstep < 0)
		v->xstep *= -1;
	v->next_h_x = v->xinter;
	v->next_h_y = v->yinter;
	ft_look_for_h_wall(main, v, i);
}

void	free_map(t_map *map)
{
	free(map->floor_colors);
	free(map->ceiling_colors);
	free_mat(map->textures);
	free_mat(map->map);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (ft_putstr_fd("Error:\n\t=>Invalid argument\n", 2), 1);
	if (!ft_init_map(av[1], &map))
		return (1);
	ft_raycasting(&map);
	free_map(&map);
	return (0);
}

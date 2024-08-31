/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:29:16 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/30 01:41:00 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_main *main, int i, double angle, t_vars *v)
{
	main->rays[i].angle = ft_adjust_angle(angle);
	main->rays[i].facing_down = main->rays[i].angle > 0
		&& main->rays[i].angle < M_PI;
	main->rays[i].facing_right = main->rays[i].angle < 0.5 * M_PI
		|| main->rays[i].angle > 1.5 * M_PI;
	v->found_hor_wall = 0;
	v->hor_wall_hit_x = 0;
	v->hor_wall_hit_y = 0;
	v->found_vert_wall = 0;
	v->vert_wall_hit_x = 0;
	v->vert_wall_hit_y = 0;
}

void	key_hook(void *param)
{
	t_main	*main;

	main = param;
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
		1 && (main->player_angle -= 2 * (M_PI / 180), main->loading = 1);
	if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		1 && (main->player_angle += 2 * (M_PI / 180), main->loading = 1);
	ft_randering(main);
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

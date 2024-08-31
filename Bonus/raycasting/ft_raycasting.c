/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 06:57:08 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/30 01:18:32 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h" 

void	ft_randering(void *param)
{
	t_main	*main;

	main = param;
	if (!main->ld)
		return ;
	ft_coloring_c_f(main);
	cast_rays(main);
	draw_3d(main);
	mini_map_draw(main);
	add_player(main);
	main->ld = 0;
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	ft_init_mlx(t_main *main)
{
	main->mlx = mlx_init(W, H, "Cube3D", false);
	if (!main->mlx)
		ft_close(main);
	main->img = mlx_new_image(main->mlx, W, H);
	if (!main->img)
		ft_close(main);
	main->texture = malloc(sizeof(mlx_texture_t) * 5);
	if (main->texture == NULL)
		ft_close(main);
	1 && (main->texture[1] = NULL, main->texture[2] = NULL);
	1 && (main->texture[3] = NULL, main->texture[4] = NULL);
	1 && (main->texture[0] = NULL), ft_load_player(main);
	main->texture[0] = mlx_load_png(main->map->textures[2]);
	if (!main->texture[0])
		ft_close(main);
	main->texture[1] = mlx_load_png(main->map->textures[1]);
	if (!main->texture[1])
		ft_close(main);
	main->texture[2] = mlx_load_png(main->map->textures[3]);
	if (!main->texture[2])
		ft_close(main);
	main->texture[3] = mlx_load_png(main->map->textures[0]);
	main->texture[4] = mlx_load_png("./pics/door.png");
	if (!main->texture[3] || !main->texture[4])
		ft_close(main);
}

void	ft_main_init(t_main *main)
{
	int	i;

	main->fov = 60 * (M_PI / 180);
	i = 0;
	while (i < 14)
		main->player_tex[i++] = NULL;
	main->ld = 1;
	main->rays = NULL;
	main->texture = NULL;
	main->mouse_use = 1;
	main->width = (ft_strlen(main->map->map[0])) * PIXEL_NBR;
	main->height = get_height(main->map->map) * PIXEL_NBR;
	1 && (main->texture = NULL, main->rays = NULL, main->img = NULL);
	ft_init_mlx(main);
	main->player_size = 4;
	main->step = PIXEL_NBR / 8;
	main->rays = malloc(sizeof(t_rays) * (W));
	if (!main->rays)
		ft_close(main);
	get_player_pos(main);
}

void	ft_raycasting(t_map *map)
{
	t_main	main;

	main.map = map;
	ft_main_init(&main);
	mlx_set_cursor_mode(main.mlx, MLX_MOUSE_HIDDEN);
	ft_randering(&main);
	mlx_image_to_window(main.mlx, main.img, 0, 0);
	mlx_loop_hook(main.mlx, key_hook, &main);
	mlx_close_hook(main.mlx, ft_close, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
}

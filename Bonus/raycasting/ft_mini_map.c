/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:37:40 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/30 01:17:25 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_border(t_main *main, int offset_x, int offset_y, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(main->img, offset_x + i, offset_y, 0x000000FF);
		mlx_put_pixel(main->img, offset_x + i, offset_y + size - 1, 0x000000FF);
		mlx_put_pixel(main->img, offset_x, offset_y + i, 0x000000FF);
		mlx_put_pixel(main->img, offset_x + size - 1, offset_y + i, 0x000000FF);
		i++;
	}
}

void	draw_map_loop(t_main *main, int x_f, int y_f)
{
	double	x;
	double	y;
	int		color;

	y = main->player_y - M_M_SIZE / 2 - 1;
	while (++y <= y_f)
	{
		x = main->player_x - M_M_SIZE / 2 - 1;
		while (++x <= x_f)
		{
			if (x < 0 || x >= main->width || y < 0 || y >= main->height)
				color = 0xf9f7f3FF;
			else if (main->map->map[(int)y / PIXEL_NBR]
				[(int)x / PIXEL_NBR] == '1')
				color = 0x0fa3b1FF;
			else if (main->map->map[(int)y / PIXEL_NBR]
				[(int)x / PIXEL_NBR] == 'D')
				color = 0xc5be15FF;
			else
				color = 0xb5e2faFF;
			mlx_put_pixel(main->img, M_M_OF_X + (SC_FACT) * (x - (main
						->player_x - M_M_SIZE / 2)), M_M_OF_Y + (SC_FACT) * (y
					- (main->player_y - M_M_SIZE / 2)), color);
		}
	}
}

void	mini_map_draw(t_main *main)
{
	int		x_f;
	int		y_f;
	double	player_screen_x;
	double	player_screen_y;

	x_f = main->player_x + M_M_SIZE / 2;
	y_f = main->player_y + M_M_SIZE / 2;
	draw_map_loop(main, x_f, y_f);
	player_screen_x = M_M_OF_X + SC_FACT * (M_M_SIZE / 2);
	player_screen_y = M_M_OF_Y + SC_FACT * (M_M_SIZE / 2);
	draw_player(main, player_screen_x, player_screen_y);
	draw_border(main, M_M_OF_X, M_M_OF_Y, M_M_SIZE * SC_FACT);
	draw_border(main, M_M_OF_X - 1,
		M_M_OF_Y - 1, M_M_SIZE * SC_FACT);
	player_screen_x += main->player_size / 2;
	player_screen_y += main->player_size / 2;
	player_screen_x /= SC_FACT;
	player_screen_y /= SC_FACT;
	dda(player_screen_x, player_screen_y, main);
}

void	key_hook(void *param)
{
	t_main	*main;
	double	p_x;
	double	p_y;
	int		xpos;
	int		ypos;

	1 && (main = param), mlx_get_mouse_pos(main->mlx, &xpos, &ypos);
	(mouse_hook(xpos, ypos, main), moves_hook(main));
	p_x = main->player_x + cos(main->player_angle) * 100;
	p_y = main->player_y + sin(main->player_angle) * 100;
	if (mlx_is_key_down(main->mlx, MLX_KEY_O) && main->map->map[(int)(p_y
			/ PIXEL_NBR)][(int)(p_x / PIXEL_NBR)] == 'D')
		1 && (main->map->map[(int)(p_y / PIXEL_NBR)]
		[(int)(p_x / PIXEL_NBR)] = 'O', main->ld = 1);
	if (mlx_is_key_down(main->mlx, MLX_KEY_C) && main->map->map[(int)(p_y
			/ PIXEL_NBR)][(int)(p_x / PIXEL_NBR)] == 'O' && main->map->map[(int)
			(main->player_y / PIXEL_NBR)]
			[(int)(main->player_x / PIXEL_NBR)] != 'O')
		1 && (main->map->map[(int)(p_y / PIXEL_NBR)]
		[(int)(p_x / PIXEL_NBR)] = 'D', main->ld = 1);
	ft_add_remove_mouse(main);
	ft_randering(main);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_main	*main;
	double	x_centre;
	double	y_centre;
	double	x;

	main = param;
	if (!main->mouse_use)
		return ;
	y_centre = H / 2;
	x_centre = W / 2;
	(void)ypos;
	x = (W / 2) - xpos;
	x /= 2;
	x *= M_PI / 180;
	if (xpos != x_centre)
	{
		main->ld = 1;
		main->player_angle -= x;
	}
	else
		return ;
	if (main->mouse_use)
		mlx_set_mouse_pos(main->mlx, (int)(W / 2), (int)(H / 2));
	ft_randering(main);
}

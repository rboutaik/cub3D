/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:05:13 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/30 01:37:19 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_close(void *param)
{
	t_main	*main;

	main = param;
	free_map(main->map);
	if (main->img)
		mlx_delete_image(main->mlx, main->img);
	if (main->texture)
	{
		if (main->texture[0])
			mlx_delete_texture(main->texture[0]);
		if (main->texture[1])
			mlx_delete_texture(main->texture[1]);
		if (main->texture[2])
			mlx_delete_texture(main->texture[2]);
		if (main->texture[3])
			mlx_delete_texture(main->texture[3]);
	}
	free(main->rays);
	free(main->texture);
	exit(0);
}

int	ft_has_wall(double x, double y, t_main *main)
{
	int	p_size;

	if (x < 0 || y < 0 || x >= main->width || y >= main->height)
		return (1);
	p_size = main->player_size;
	if (main->map->map[(int)floor((y)
				/ PIXEL_NBR)][(int)floor((x) / PIXEL_NBR)] != '1'
	&& main->map->map[(int)floor((y + 14)
			/ PIXEL_NBR)][(int)floor((x + 14) / PIXEL_NBR)] != '1'
	&& main->map->map[(int)floor((y)
			/ PIXEL_NBR)][(int)floor((x + 14) / PIXEL_NBR)] != '1'
	&& main->map->map[(int)floor((y + 14)
			/ PIXEL_NBR)][(int)floor((x) / PIXEL_NBR)] != '1'
	&& main->map->map[(int)floor((y - 14)
			/ PIXEL_NBR)][(int)floor((x - 14) / PIXEL_NBR)] != '1'
	&& main->map->map[(int)floor((y)
			/ PIXEL_NBR)][(int)floor((x - 14) / PIXEL_NBR)] != '1'
	&& main->map->map[(int)floor((y - 14)
			/ PIXEL_NBR)][(int)floor((x) / PIXEL_NBR)] != '1')
		return (0);
	return (1);
}

void	ft_turn(t_main *main, int redir, double new_x, double new_y)
{
	main->loading = 1;
	if (redir == TOP)
		1 && (new_x = main->player_x + cos(main->player_angle) * main->step,
			new_y = main->player_y + sin(main->player_angle) * main->step);
	else if (redir == BOTTOM)
	{
		new_x = main->player_x - cos(main->player_angle) * main->step;
		new_y = main->player_y - sin(main->player_angle) * main->step;
	}
	else if (redir == LEFT)
	{
		new_x = main->player_x + cos(main->player_angle - 90
				* (M_PI / 180)) * main->step;
		new_y = main->player_y + sin(main->player_angle - 90
				* (M_PI / 180)) * main->step;
	}
	else if (redir == RIGHT)
	{
		new_x = main->player_x + cos(main->player_angle + 90
				* (M_PI / 180)) * main->step;
		new_y = main->player_y + sin(main->player_angle + 90
				* (M_PI / 180)) * main->step;
	}
	if (!ft_has_wall(new_x, new_y, main))
		1 && (main->player_x = new_x, main->player_y = new_y);
}

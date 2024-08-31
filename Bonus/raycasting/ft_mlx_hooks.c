/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:05:13 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/30 01:39:22 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_close(void *param)
{
	t_main	*main;
	int		i;

	main = param;
	free_map(main->map);
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
		if (main->texture[4])
			mlx_delete_texture(main->texture[4]);
	}
	i = -1;
	while (++i < 14)
		if (main->player_tex[i] != NULL)
			mlx_delete_texture(main->player_tex[i]);
	(free(main->rays), free(main->texture));
	exit(0);
}

int	check_for_door(double x, double y, t_main *main)
{
	if ((main->map->map[(int)floor((y)
					/ PIXEL_NBR)][(int)floor((x) / PIXEL_NBR)] == 'D'
		|| main->map->map[(int)floor((y + 14)
				/ PIXEL_NBR)][(int)floor((x + 14) / PIXEL_NBR)] == 'D'
	|| main->map->map[(int)floor((y)
				/ PIXEL_NBR)][(int)floor((x + 14) / PIXEL_NBR)] == 'D'
	|| main->map->map[(int)floor((y + 14)
				/ PIXEL_NBR)][(int)floor((x) / PIXEL_NBR)] == 'D'))
		return (1);
	return (0);
}

int	ft_has_wall(double x, double y, t_main *main)
{
	if (x < 0 || y < 0 || x >= main->width || y >= main->height)
		return (1);
	if (check_for_door(x, y, main))
		return (1);
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
	1 && (main->p_idx = (main->p_idx + 1) % 14, main->ld = 1);
}

void	ft_add_remove_mouse(t_main *main)
{
	if (mlx_is_key_down(main->mlx, MLX_KEY_Z))
		(1) && (main->mouse_use = 0)
			, mlx_set_cursor_mode(main->mlx, MLX_MOUSE_NORMAL);
	if (mlx_is_key_down(main->mlx, MLX_KEY_X))
		1 && (main->mouse_use = 1)
			, mlx_set_cursor_mode(main->mlx, MLX_MOUSE_HIDDEN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:40:24 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/30 00:29:36 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_main *main, double y, double x)
{
	if (x / PIXEL_NBR < 0 || x / PIXEL_NBR >= main->width
		|| y / PIXEL_NBR < 0 || x / PIXEL_NBR >= main->height)
		return (1);
	if (main->map->map[(int)floor((y) / PIXEL_NBR)]
		[(int)floor((x) / PIXEL_NBR)] == '1')
		return (1);
	return (0);
}

void	ft_look_for_h_wall(t_main *main, t_vars *v, int i)
{
	while (v->next_h_x >= 0 && v->next_h_x < main->width
		&& v->next_h_y >= 0 && v->next_h_y < main->height)
	{
		v->x_to_check = v->next_h_x;
		v->y_to_check = v->next_h_y;
		if (!main->rays[i].facing_down)
			v->y_to_check--;
		if (is_wall(main, v->y_to_check, v->x_to_check))
		{
			v->hor_wall_hit_x = v->next_h_x;
			v->hor_wall_hit_y = v->next_h_y;
			v->found_hor_wall = 1;
			break ;
		}
		else
		{
			v->next_h_x += v->xstep;
			v->next_h_y += v->ystep;
		}
	}
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

void	look_for_v_wall(t_main *main, t_vars *v, int i)
{
	while (v->next_v_x >= 0 && v->next_v_x < main->width
		&& v->next_v_y >= 0 && v->next_v_y < main->height)
	{
		v->x_to_check = v->next_v_x;
		if (!main->rays[i].facing_right)
			v->x_to_check--;
		v->y_to_check = v->next_v_y;
		if (is_wall(main, v->y_to_check, v->x_to_check))
		{
			v->vert_wall_hit_x = v->next_v_x;
			v->vert_wall_hit_y = v->next_v_y;
			v->found_vert_wall = 1;
			break ;
		}
		else
		{
			v->next_v_x += v->xstep;
			v->next_v_y += v->ystep;
		}
	}
}

double	ft_distance(double x, double y, t_main *main)
{
	double	distance;

	distance = sqrt((x - main->player_x) * (x - main->player_x)
			+ (y - main->player_y) * (y - main->player_y));
	return (distance);
}

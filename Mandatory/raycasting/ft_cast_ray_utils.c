/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_ray_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:44:07 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/20 09:31:01 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	distance_calc(t_main *main, t_vars *v)
{
	if (v->found_hor_wall)
		v->hor_hit_distance = ft_distance(v->hor_wall_hit_x,
				v->hor_wall_hit_y, main);
	else
		v->hor_hit_distance = INT_MAX;
	if (v->found_vert_wall)
		v->vert_hit_distance = ft_distance(v->vert_wall_hit_x,
				v->vert_wall_hit_y, main);
	else
		v->vert_hit_distance = INT_MAX;
}

void	cast_one_ray(t_main *main, double angle, int i)
{
	t_vars	v;

	init_vars(main, i, angle, &v);
	hor_inter(main, i, &v);
	vert_inter(main, i, &v);
	distance_calc(main, &v);
	if (v.vert_hit_distance < v.hor_hit_distance)
	{
		main->rays[i].distance = v.vert_hit_distance;
		main->rays[i].wall_x_hit = v.vert_wall_hit_x;
		main->rays[i].wall_y_hit = v.vert_wall_hit_y;
		main->rays[i].side_wall_hit = true;
	}
	else
	{
		main->rays[i].distance = v.hor_hit_distance;
		main->rays[i].wall_x_hit = v.hor_wall_hit_x;
		main->rays[i].wall_y_hit = v.hor_wall_hit_y;
		main->rays[i].side_wall_hit = false;
	}
}

void	cast_rays(t_main *main)
{
	double	angle;
	int		i;

	angle = main->player_angle - (main->fov / 2);
	i = 0;
	while (i < W)
	{
		cast_one_ray(main, angle, i);
		angle += main->fov / W;
		i++;
	}
}

double	ft_adjust_angle(double angle)
{
	double	new_angle;

	new_angle = fmod(angle, (2 * M_PI));
	if (new_angle < 0)
		new_angle += 2 * M_PI;
	return (new_angle);
}

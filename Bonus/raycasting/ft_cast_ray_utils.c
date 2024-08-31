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

#include "../cub3d_bonus.h"

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

void	hor_fill(t_main *main, t_vars *v, int i)
{
	main->rays[i].distance = v->hor_hit_distance;
	main->rays[i].wall_x_hit = v->hor_wall_hit_x;
	main->rays[i].wall_y_hit = v->hor_wall_hit_y;
	main->rays[i].side_wall_hit = false;
	if (!main->rays[i].facing_down)
		main->rays[i].content = main->map->map
		[(int)floor((main->rays[i].wall_y_hit - 1) / PIXEL_NBR)]
		[(int)floor((main->rays[i].wall_x_hit) / PIXEL_NBR)];
	else
		main->rays[i].content = main->map->map
		[(int)floor(main->rays[i].wall_y_hit / PIXEL_NBR)]
		[(int)floor(main->rays[i].wall_x_hit / PIXEL_NBR)];
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
		if (!main->rays[i].facing_right)
			main->rays[i].content = main->map->map
			[(int)floor(main->rays[i].wall_y_hit / PIXEL_NBR)]
			[(int)floor((main->rays[i].wall_x_hit - 1) / PIXEL_NBR)];
		else
			main->rays[i].content = main->map->map
			[(int)floor(main->rays[i].wall_y_hit / PIXEL_NBR)]
			[(int)floor(main->rays[i].wall_x_hit / PIXEL_NBR)];
	}
	else
	{
		hor_fill(main, &v, i);
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

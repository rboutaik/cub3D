/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:39:33 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/20 09:31:01 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_coloring_c_f(t_main *main)
{
	int	i;
	int	j;

	i = -1;
	while (++i < H / 2)
	{
		j = -1;
		while (++j < W)
			mlx_put_pixel(main->img, j, i,
				ft_color(main->map->ceiling_colors[0],
					main->map->ceiling_colors[1],
					main->map->ceiling_colors[2], 255));
	}
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			mlx_put_pixel(main->img, j, i, ft_color(main->map->floor_colors[0],
					main->map->floor_colors[1],
					main->map->floor_colors[2], 255));
			j++;
		}
		i++;
	}
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	int		index;

	if (x >= 0 && (uint32_t)x < texture->width
		&& y >= 0 && (uint32_t)y < texture->height)
	{
		index = (y * texture->width + x) * 4;
		r = texture->pixels[index];
		g = texture->pixels[index + 1];
		b = texture->pixels[index + 2];
		a = texture->pixels[index + 3];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0x00000000);
}

int	get_tex_idx(t_main *main, int i)
{
	if (main->rays[i].content == 'D')
		return (4);
	if (main->rays[i].side_wall_hit)
	{
		if (main->rays[i].facing_right)
			return (0);
		else
			return (1);
	}
	else if (main->rays[i].facing_down)
		return (2);
	else
		return (3);
}

void	wall_vars_init(t_main *main, t_wall_vars *v)
{
	v->proj_distance = (W / 2) / tan(main->fov / 2);
	v->correct_distance = main->rays[v->i].distance
		* cos(main->rays[v->i].angle - main->player_angle);
	v->proj_wall_h = (PIXEL_NBR / v->correct_distance) * v->proj_distance;
	v->p_wall_height = (int)v->proj_wall_h;
	v->wall_top_pixel = (H / 2) - (v->p_wall_height / 2);
	if (v->wall_top_pixel < 0)
		v->wall_top_pixel = 0;
	else
		v->wall_top_pixel = v->wall_top_pixel;
	v->wall_bottom_pixel = (H / 2) + (v->p_wall_height / 2);
	if (v->wall_bottom_pixel > H)
		v->wall_bottom_pixel = H;
	else
		v->wall_bottom_pixel = v->wall_bottom_pixel;
	v->j = v->wall_top_pixel;
}

void	draw_3d(t_main *main)
{
	t_wall_vars	v;

	v.i = 0;
	while (v.i < W)
	{
		wall_vars_init(main, &v);
		v.tex_idx = get_tex_idx(main, v.i);
		if (main->rays[v.i].side_wall_hit)
			v.wall_x = main->rays[v.i].wall_y_hit;
		else
			v.wall_x = main->rays[v.i].wall_x_hit;
		v.wall_x = (int)v.wall_x % PIXEL_NBR;
		v.wall_x = (main->texture[v.tex_idx]->width * v.wall_x) / PIXEL_NBR;
		while (v.j < v.wall_bottom_pixel)
		{
			v.tex_y = (v.j - ((H / 2) - (v.p_wall_height / 2)));
			v.tex_y = (v.tex_y * main->texture[v.tex_idx]->height)
				/ (v.p_wall_height);
			mlx_put_pixel(main->img, v.i, v.j,
				get_texture_pixel(main->texture[v.tex_idx], v.wall_x, v.tex_y));
			v.j++;
		}
		v.i++;
	}
}

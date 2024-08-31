/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:41:56 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/20 09:25:38 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	dda(double X0, double Y0, t_main *main)
{
	int		steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;

	x = X0 + cos(main->player_angle) * 50;
	y = Y0 + sin(main->player_angle) * 50;
	y = round(y) - round(Y0);
	x = round(x) - round(X0);
	if (fabs(x) > fabs(y))
		steps = fabs(x);
	else
		steps = fabs(y);
	x_inc = x / (double)steps;
	y_inc = y / (double)steps;
	x = X0;
	y = Y0;
	while (steps-- >= 0)
	{
		mlx_put_pixel(main->img, SC_FACT * round(x),
			SC_FACT * round(y), 0xFF0000FF);
		x += x_inc;
		y += y_inc;
	}
}

double	ft_get_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (3 * (M_PI / 2));
	if (c == 'W')
		return (M_PI);
	if (c == 'S')
		return (M_PI / 2);
	return (0);
}

void	get_player_pos(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	while (i < main->height)
	{
		j = 0;
		while (j < main->width)
		{
			if (ft_strchr("EWNS", main->map->map[i / PIXEL_NBR][j / PIXEL_NBR]))
			{
				main->player_x = j + main->player_size / 2;
				main->player_y = i + main->player_size / 2;
				main->player_angle = ft_get_angle(main->map->map[i
						/ PIXEL_NBR][j / PIXEL_NBR]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	draw_player(t_main *main, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < main->player_size)
	{
		j = 0;
		while (j < main->player_size)
		{
			mlx_put_pixel(main->img, j + x, i + y, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

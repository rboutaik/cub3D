/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:50:43 by rboutaik          #+#    #+#             */
/*   Updated: 2024/08/19 13:09:55 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	add_player(t_main *main)
{
	double		p_x;
	double		p_y;
	double		x;
	double		y;
	uint32_t	color;

	p_x = (W / 2) - main->player_tex[main->p_idx]->width / 2;
	p_y = H / 2;
	y = 0;
	while (y < main->player_tex[main->p_idx]->height)
	{
		x = 0;
		while (x < main->player_tex[main->p_idx]->width)
		{
			color = get_texture_pixel(main->player_tex[main->p_idx], x, y);
			if (color)
				mlx_put_pixel(main->img, x + p_x, y + p_y, color);
			x++;
		}
		y++;
	}
}

void	ft_load_player(t_main *main)
{
	int	i;

	main->p_imgs[0] = "./pics/CJ1.png";
	main->p_imgs[1] = "./pics/CJ2.png";
	main->p_imgs[2] = "./pics/CJ3.png";
	main->p_imgs[3] = "./pics/CJ4.png";
	main->p_imgs[4] = "./pics/CJ5.png";
	main->p_imgs[5] = "./pics/CJ6.png";
	main->p_imgs[6] = "./pics/CJ7.png";
	main->p_imgs[7] = "./pics/CJ8.png";
	main->p_imgs[8] = "./pics/CJ9.png";
	main->p_imgs[9] = "./pics/CJ10.png";
	main->p_imgs[10] = "./pics/CJ11.png";
	main->p_imgs[11] = "./pics/CJ12.png";
	main->p_imgs[12] = "./pics/CJ13.png";
	main->p_imgs[13] = "./pics/CJ14.png";
	main->p_imgs[14] = NULL;
	main->p_idx = 0;
	i = -1;
	while (main->p_imgs[++i])
	{
		main->player_tex[i] = mlx_load_png(main->p_imgs[i]);
		if (!main->player_tex[i])
			ft_close(main);
	}
}

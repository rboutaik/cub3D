/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:03:23 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/25 18:25:58 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	get_size_mat(char **mat)
{
	int		i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

int	check_walls_door(char **map, int i, int j)
{
	int		w;
	int		h;

	h = get_size_mat(map);
	w = ft_strlen(map[0]);
	return ((i - 1 >= 0 && i + 1 < h
			&& map[i - 1][j] == '1'
		&& map[i + 1][j] == '1')
				|| (j - 1 >= 0 && j + 1 < w
				&& map[i][j - 1] == '1'
				&& map[i][j + 1] == '1'));
}

int	ft_check_doors(char **map)
{
	int		i;
	int		j;

	(1) && (i = -1);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D' && !check_walls_door(map, i, j))
				return (ft_putstr_fd("Error\n\t=>invalid position of door\n",
						2), 0);
		}
	}
	return (1);
}

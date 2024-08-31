/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:21:10 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/29 20:24:39 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	is_charcters(char c)
{
	return (c == '0' || c == '1' || c == 'S'
		|| c == 'N' || c == 'W' || c == 'E'
		|| (c == 32) || (c == 'D'));
}

static int	get_index_player(char c)
{
	char	*str;
	int		i;

	i = -1;
	str = "NWES";
	while (str[++i])
	{
		if (ft_strchr(str, c))
			return (i);
	}
	return (-1);
}

static int	count_player_charcters(int count_player)
{
	if (count_player != 1)
		return (ft_putstr_fd("Error:\n\t==>invalid player\n", 2), 0);
	return (1);
}

int	ft_check_charcters(char **map, char **(*fun2)(char **map))
{
	int		i;
	int		j;
	char	**walls;
	int		player;
	int		index;

	walls = fun2(map);
	if (!walls)
		return (0);
	(1) && (i = -1, player = 0);
	while (walls[++i])
	{
		j = -1;
		while (walls[i][++j])
		{
			index = get_index_player(walls[i][j]);
			if (!is_charcters(walls[i][j]))
				return (ft_putstr_fd("Error:\n\t==>invalid charcters \n"
						, 2), 0);
			else if (index >= 0)
				player++;
		}
	}
	return (count_player_charcters(player));
}

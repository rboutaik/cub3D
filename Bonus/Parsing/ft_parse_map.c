/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:23:02 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/25 18:24:52 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	is_character(char c)
{
	return (c == '0' || c == 'S' || c == 'W'
		|| c == 'E' || c == 'N' || c == 'D');
}

static int	str_is_whitespaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	return (i == ft_strlen(str));
}

static void	ft_remove_new_lines(char **map, int i)
{
	while (map[i])
	{
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = '\0';
		i++;
	}
}

static char	**get_walls(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		if (!str_is_whitespaces(map[i]) && ft_strncmp(map[i], "NO ", 3)
			&& ft_strncmp(map[i], "SO ", 3)
			&& ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)
			&& ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2))
			break ;
	}
	j = i - 1;
	while (map[++j])
	{
		if (map[j][0] == '\n')
			return (ft_putstr_fd("Error:\n\t==>invalid charcters \n"
					, 2), NULL);
	}
	ft_remove_new_lines(map, i);
	return (&map[i]);
}

char	**ft_parse_map(char *file)
{
	char	**map;

	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		return (ft_putstr_fd("Error:\n\t=>invalid extantion .cub\n", 2), NULL);
	map = ft_get_map(file);
	if (!map)
		return (NULL);
	if (ft_check_textures(map) && ft_check_colors_fc(map)
		&& ft_check_charcters(map, get_walls)
		&& ft_check_wall(map, is_character, get_walls))
		return (map);
	return (free_mat(map), NULL);
}

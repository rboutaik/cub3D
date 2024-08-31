/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:10:53 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/25 18:31:11 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	*char_to_int(char **numbers_char)
{
	int		*numbers_int;
	int		i;
	int		j;

	numbers_int = malloc(sizeof(int) * 3);
	if (!numbers_int)
		return (NULL);
	i = -1;
	j = 1;
	while (numbers_char[++i] && j < 3)
	{
		if (i == 0)
		{
			j = 1;
			while (numbers_char[i][j] && numbers_char[i][j] != 32)
				j++;
			numbers_int[0] = ft_atoi(&numbers_char[i][j]);
			j = 1;
		}
		else
			numbers_int[j++] = ft_atoi(numbers_char[i]);
	}
	return (free_mat(numbers_char), numbers_int);
}

static int	*get_colors(char **map, char *str)
{
	int		i;
	char	**split_numbers;
	int		j;

	i = -1;
	while (map[++i])
	{
		if (!ft_strncmp(str, map[i], 2))
		{
			j = -1;
			split_numbers = ft_split(map[i], ',');
			if (!split_numbers)
				return (NULL);
			return (char_to_int(split_numbers));
		}
	}
	return (NULL);
}

static int	get_index_textures(char *str)
{
	char	**split_textures;
	char	*postion;
	int		i;

	postion = "NO,WE,EA,SO";
	split_textures = ft_split(postion, ',');
	if (!split_textures)
		return (-1);
	i = -1;
	while (split_textures[++i])
	{
		if (!ft_strncmp(str, split_textures[i], 2))
			return (free_mat(split_textures), i);
	}
	return (free_mat(split_textures), -1);
}

static char	**get_textures(char **map)
{
	char	**textures;
	int		j;
	int		i;
	int		count_textures;
	int		index;

	textures = malloc(sizeof(char *) * 5);
	if (!textures)
		return (NULL);
	(1) && (i = -1, count_textures = 0);
	while (map[++i] && count_textures <= 4)
	{
		index = get_index_textures(map[i]);
		if (index != -1)
		{
			(1) && (j = 2, count_textures++);
			while (map[i][j] && map[i][j] == 32)
				j++;
			textures[index] = ft_strdup(&map[i][j]);
			if (!textures[index])
				return (free_mat(textures), NULL);
			textures[index][ft_strlen(textures[index]) - 1] = '\0';
		}
	}
	return (textures[count_textures] = NULL, textures);
}

int	ft_init_map(char *file, t_map *map)
{
	char	**map_parse;

	map_parse = ft_parse_map(file);
	if (!map_parse)
		return (0);
	map->ceiling_colors = get_colors(map_parse, "C ");
	if (!map->ceiling_colors)
		return (free_mat(map_parse), 0);
	map->floor_colors = get_colors(map_parse, "F ");
	if (!map->floor_colors)
		return (free(map->ceiling_colors),
			free_mat(map_parse), 0);
	map->textures = get_textures(map_parse);
	if (!map->textures)
		return (free(map->ceiling_colors), free(map->floor_colors),
			free_mat(map_parse), 0);
	map->map = ft_get_map_rectangel(map_parse);
	if (!map->map)
		return (free(map->ceiling_colors), free(map->floor_colors),
			free_mat(map->textures), free_mat(map_parse), 0);
	if (!ft_check_doors(map->map))
		return (free(map->ceiling_colors), free(map->floor_colors),
			free_mat(map->textures),
			free_mat(map_parse), free_mat(map->map), 0);
	return (free_mat(map_parse), 1);
}

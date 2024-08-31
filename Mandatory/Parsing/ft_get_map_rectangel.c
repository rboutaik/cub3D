/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_rectangel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:40:25 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/18 00:07:27 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**get_walls(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && (map[i][j] == 32 || map[i][j] == '\n'))
			j++;
		if ((j != ft_strlen(map[i])) && ft_strncmp(map[i], "NO ", 3)
			&& ft_strncmp(map[i], "SO ", 3)
			&& ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)
			&& ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2))
			break ;
	}
	return (&map[i]);
}

static int	get_max_line(char **map, int *size)
{
	int		i;
	int		max_line;
	int		len;

	(1) && (i = -1, max_line = -1);
	if (!map || !map[0])
		return (-1);
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		if (len > max_line)
			max_line = len;
	}
	return (*size = i, max_line);
}

static char	*add_spaces(char *str, int size)
{
	int		i;
	char	*tmp;

	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		tmp[i] = str[i];
	while (i < size)
		tmp[i++] = 32;
	tmp[size] = '\0';
	return (tmp);
}

static char	**make_map_rectangle(char **map)
{
	int		i;
	int		max_line;
	char	**new_map;
	char	**walls;
	int		size;

	if (!*map || !map)
		return (NULL);
	walls = get_walls(map);
	(1) && (max_line = get_max_line(walls, &size), i = 0);
	if (max_line < 0)
		return (ft_putstr_fd("Error:\n\t==> there is no map\n", 2), NULL);
	new_map = malloc(sizeof(char *) * (size + 1));
	if (!new_map)
		return (NULL);
	i = -1;
	while (walls[++i])
	{
		new_map[i] = add_spaces(walls[i], max_line);
		if (!new_map[i])
			return (free_mat(new_map), perror("memory problem"), NULL);
	}
	new_map[size] = NULL;
	return (new_map);
}

char	**ft_get_map_rectangel(char **map)
{
	if (!map || !*map)
		return (NULL);
	return (make_map_rectangle(map));
}

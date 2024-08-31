/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:07:31 by youbrhic          #+#    #+#             */
/*   Updated: 2024/07/27 08:39:00 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_map_len(char *file)
{
	char	*tmp;
	int		count;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	tmp = get_next_line(fd);
	count = 0;
	while (tmp)
	{
		free(tmp);
		count++;
		tmp = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	free_index(char **map)
{
	int		i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

char	**ft_get_map(char *file)
{
	int		fd;
	char	**map;
	char	*line;
	int		map_size;
	int		i;

	map_size = get_map_len(file);
	if (!map_size)
		return (ft_putstr_fd("Error :\n\t==>empty file", 2), NULL);
	map = malloc(sizeof(char *) * (map_size + 1));
	if (!map)
		return (perror("malloc"), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), NULL);
	(1) && (line = get_next_line(fd), i = 0);
	while (line)
	{
		map[i] = ft_strdup(line);
		if (!map[i])
			return (perror("malloc"), free_index(map), close(fd), NULL);
		free(line);
		(1) && (line = get_next_line(fd), i++);
	}
	return (map[i] = NULL, close(fd), map);
}

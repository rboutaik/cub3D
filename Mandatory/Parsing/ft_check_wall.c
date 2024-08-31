/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 05:34:29 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/30 01:52:44 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static char	**make_map_rectangle(char **map, int *size)
{
	int		i;
	int		max_line;
	char	**new_map;

	(1) && (max_line = get_max_line(map, size), i = 0);
	if (max_line < 0)
		return (ft_putstr_fd("Error:\n\t=> there is no map\n", 2), NULL);
	new_map = malloc(sizeof(char *) * (*size + 1));
	if (!new_map)
		return (NULL);
	while (map[i])
	{
		new_map[i] = add_spaces(map[i], max_line);
		if (!new_map[i])
			return (free_mat(new_map), perror("memory problem"), NULL);
		i++;
	}
	new_map[*size] = NULL;
	return (new_map);
}

static int	is_space(char c)
{
	return (c == 32);
}

int	ft_check_wall(char **map, int (*fun1)(char c), char **(*fun2)(char **map))
{
	char	**new_map;
	int		i;
	int		j;
	int		row_column[2];

	new_map = make_map_rectangle(fun2(map), &row_column[1]);
	if (!new_map)
		return (1);
	(1) && (row_column[0] = ft_strlen(new_map[0]), i = -1);
	while (new_map[++i])
	{
		j = -1;
		while (new_map[i][++j])
		{
			if (fun1(new_map[i][j]) && ((j == 0 || j == row_column[0] - 1)
					|| (i == 0 || i == row_column[1] - 1)
					|| (i - 1 >= 0 && is_space(new_map[i - 1][j]))
					|| (i + 1 < row_column[1] && is_space(new_map[i + 1][j]))
					|| (j - 1 >= 0 && is_space(new_map[i][j - 1]))
					|| (j + 1 < row_column[0] && is_space(new_map[i][j + 1]))))
				return (ft_putstr_fd("Error:\n\t=>not closed by walls\n", 2)
					, free_mat(new_map), 0);
		}
	}
	return (free_mat(new_map), 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors_fc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:40:01 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/25 17:27:14 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_textures_space(char *str)
{
	int		i;
	int		space;

	i = -1;
	space = 1;
	while (str[++i])
		if (str[i] == 32 || str[i] == '\t')
			space = 0;
	return (space || !ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3));
}

static int	check_syntax_color(char *str)
{
	char	**rgb;
	int		i;

	i = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 12) || str[i] == 32))
		i++;
	rgb = ft_split(&str[i], ',');
	if (!rgb)
		return (ft_putstr_fd("Error\n\t", 2),
			perror("==> malloc"), free_mat(rgb), 0);
	i = -1;
	while (rgb[++i] && i < 4)
	{
		if (((rgb[i][0] >= 9 && rgb[i][0] <= 12) || rgb[i][0] == 32)
				|| (rgb[i][0] != '\n' && ft_atoi(rgb[i]) < 0)
				|| rgb[i][0] < '0' || rgb[i][0] > '9')
			return (ft_putstr_fd("Error : \n\t =>invalid RGB colors\n", 2),
				free_mat(rgb), 0);
	}
	if (i != 3)
		return (ft_putstr_fd("Error : \n\t =>invalid RGB colors\n", 2),
			free_mat(rgb), 0);
	return (free_mat(rgb), 1);
}

static int	increment_count_colors(int *nb1, int *nb2, char *str)
{
	int		i;
	int		cmp_f;
	int		cmp_c;
	int		count_comma;

	cmp_f = !ft_strncmp(str, "C ", 2);
	cmp_c = !ft_strncmp(str, "F ", 2);
	if ((cmp_c || cmp_f) && (!check_syntax_color(str)))
		return (0);
	(1) && (i = -1, count_comma = 0);
	while (str[++i])
		if (str[i] == ',')
			count_comma++;
	if (count_comma > 2)
		return (ft_putstr_fd("Error:\n\t=>invalid RGB colors\n", 2), 0);
	if (cmp_f)
		*nb1 += 1;
	else if (cmp_c)
		*nb2 += 1;
	return (1);
}

static int	check_count_color(int *tab)
{
	int		i;

	i = -1;
	while (++i < 2)
	{
		if (tab[i] > 1 || tab[i] == 0)
			return (ft_putstr_fd("Error:\n\t=>invalid RGB colors\n", 2), 0);
	}
	return (1);
}

int	ft_check_colors_fc(char **map)
{
	int	count_colors[2];
	int	i;

	i = -1;
	ft_bzero(count_colors, 8);
	while (map[++i])
	{
		if (!is_textures_space(map[i]) && ft_strncmp(map[i], "F ", 2)
			&& ft_strncmp(map[i], "C ", 2))
			break ;
		if (!increment_count_colors(&count_colors[0], &count_colors[1], map[i]))
			return (0);
	}
	return (check_count_color(count_colors));
}

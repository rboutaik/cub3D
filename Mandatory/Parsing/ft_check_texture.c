/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:35:19 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/24 17:27:35 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**get_textures(void)
{
	char	**textures;

	textures = malloc(sizeof(char *) * 5);
	if (!textures)
		return (NULL);
	textures[0] = "NO ";
	textures[1] = "SO ";
	textures[2] = "WE ";
	textures[3] = "EA ";
	textures[4] = NULL;
	return (textures);
}

static int	get_index_texture(char *str)
{
	int		i;
	char	**textures;

	i = -1;
	textures = get_textures();
	if (!textures)
		return (-1);
	while (textures[++i])
		if (!ft_strncmp(str, textures[i], 3))
			return (free(textures), i);
	return (free(textures), -1);
}

static int	check_count(int *tab)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (tab[i] > 1 || tab[i] == 0)
			return (ft_putstr_fd("Error:\n\t==>invalid textures\n", 2), 0);
	}
	return (1);
}

static int	check_whitespace(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == 32 || str[i] == '\t')
			return (0);
	return (1);
}

int	ft_check_textures(char **map)
{
	int		i;
	int		count_textures[4];
	int		index_texture;

	ft_bzero(count_textures, 16);
	i = -1;
	while (map[++i])
	{
		index_texture = get_index_texture(map[i]);
		if (index_texture < 0 && !(!ft_strncmp(map[i], "F ", 2)
				|| !ft_strncmp(map[i], "C ", 2) || check_whitespace(map[i])))
			break ;
		else if (index_texture >= 0)
			count_textures[index_texture]++;
	}
	return (check_count(count_textures));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 05:25:11 by youbrhic          #+#    #+#             */
/*   Updated: 2024/07/13 17:39:26 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char *src)
{
	char	*temp;
	int		i;

	if (!src || !src[0])
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	i += (src[i] == '\n');
	temp = malloc(i + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		temp[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

char	*get_other_line(char *start)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (start[i] && start[i] != '\n')
		i++;
	if (start[i] == '\0')
	{
		free(start);
		return (NULL);
	}
	i += (start[i] == '\n');
	new = malloc(1 + len(start) - i);
	if (!new)
		return (NULL);
	j = 0;
	while (start [i + j])
	{
		new[j] = start[i + j];
		j++;
	}
	new[j] = '\0';
	free(start);
	return (new);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*line;
	int			read_fd;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	read_fd = 1;
	tmp = malloc(1 + BUFFER_SIZE);
	if (!tmp)
		return (NULL);
	while (!(found_char(line, '\n')) && read_fd != 0)
	{
		read_fd = read(fd, tmp, BUFFER_SIZE);
		if (read_fd == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp [read_fd] = '\0';
		line = ft_join(line, tmp);
	}
	free(tmp);
	tmp = read_line(line);
	line = get_other_line(line);
	return (tmp);
}

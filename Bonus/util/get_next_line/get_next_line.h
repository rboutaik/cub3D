/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:08:12 by youbrhic          #+#    #+#             */
/*   Updated: 2024/07/21 05:56:56 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

size_t	len(const char *str);
char	*get_next_line(int fd);
char	*read_line(char *src);
int		found_char(char *str, char c);
char	*get_other_line(char *start);
char	*ft_join(char *start, char *buff);
char	*ft_join2(char *dest, char *s1, char *s2);

#endif

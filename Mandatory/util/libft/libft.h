/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:23:08 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/19 17:41:11 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <libc.h>

// First Part
void				ft_bzero(void *s, size_t n);
void				free_mat(char **map);
int					ft_strlen(const char *s);
char				*ft_strdup(const char *src);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
// second part 
char				**ft_split(char const *s, char c);
void				ft_putstr_fd(char *s, int fd);

#endif

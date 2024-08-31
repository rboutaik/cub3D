# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 18:01:35 by youbrhic          #+#    #+#              #
#    Updated: 2024/08/31 19:20:30 by rboutaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

FILES_LVL1 = main.c

FILES_LVL2 =Parsing/ft_check_texture.c Parsing/ft_check_characters.c Parsing/ft_get_map.c Parsing/ft_init_map.c raycasting/ft_mlx_hooks.c raycasting/ft_raycasting.c \
			Parsing/ft_check_colors_fc.c Parsing/ft_check_wall.c Parsing/ft_get_map_rectangel.c Parsing/ft_parse_map.c \
			raycasting/ft_walls.c raycasting/ft_cast_ray.c raycasting/utils.c raycasting/ft_cast_ray_utils.c

FILES_LVL3 =util/get_next_line/get_next_line.c util/libft/free_mat.c  util/libft/ft_putstr_fd.c util/libft/ft_strlen.c \
			  util/libft/ft_atoi.c   util/libft/ft_split.c   util/libft/ft_strncmp.c  util/libft/ft_strchr.c \
			  util/get_next_line/get_next_line_utils.c util/libft/ft_bzero.c   util/libft/ft_strdup.c

Man = Mandatory/

Bon = Bonus/

FILES_MAN = $(FILES_LVL1) $(FILES_LVL2) $(FILES_LVL3)

FILES_BON  = $(FILES_LVL1) $(FILES_LVL2) $(FILES_LVL3) raycasting/ft_anime.c raycasting/ft_mini_map.c Parsing/ft_check_doors.c

Mandatory = $(addprefix $(Man), $(FILES_MAN)) 

Bonus = $(addprefix $(Bon), $(FILES_BON))

OBJS = $(Mandatory:.c=.o)

OBJS_BON = $(Bonus:.c=.o)

RM = rm -f

INCLUDES = $(Man)cub3d.h $(Man)util/libft/libft.h  $(Man)util/get_next_line/get_next_line.h

INCLUDES_BON = $(Bon)cub3d_bonus.h $(Bon)util/libft/libft.h  $(Bon)util/get_next_line/get_next_line.h

CC = cc 

CFLAGS = -Wall -Wextra -Werror

LIBMLX = libmlx42.a

INCLUDES_MLX42 = MLX42.h


all : $(NAME)

bonus : $(NAME_BONUS)

Mandatory/%.o : Mandatory/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -I /Users/$(USER)/MLX42/include/MLX42 -o $@ -c $<

Bonus/%.o : Bonus/%.c $(INCLUDES_BON)
	$(CC) $(CFLAGS) -I /Users/$(USER)/MLX42/include/MLX42  -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(LIBMLX)  \
	-lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib/"

$(NAME_BONUS) :$(OBJS_BON)
    $(NAME_BONUS): $(OBJS_BON)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BON)  \
	$(LIBMLX) -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib/"

clean :
	$(RM) $(OBJS) $(OBJS_BON)

fclean : clean
	$(RM) $(NAME) $(NAME_BONUS)

re : fclean all
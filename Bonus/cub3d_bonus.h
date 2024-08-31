/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:02:19 by youbrhic          #+#    #+#             */
/*   Updated: 2024/08/31 19:20:01 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../MLX42.h"
# include <math.h>
# include "util/get_next_line/get_next_line.h"
# include "util/libft/libft.h"

# define LEFT 0
# define RIGHT 1
# define TOP 2
# define BOTTOM 3
# define PIXEL_NBR 200
# define SC_FACT 0.2
# define M_M_SIZE 800
# define W 1080
# define H 750

# define M_M_OF_X 50
# define M_M_OF_Y 50 

typedef struct s_rays
{
	double	distance;
	double	angle;
	int		side_wall_hit;
	double	wall_x_hit;
	double	wall_y_hit;
	int		facing_down;
	int		facing_right;
	char	content;
}	t_rays;

typedef struct s_map
{
	int		*floor_colors;
	int		*ceiling_colors;
	char	**textures;
	char	**map;
}			t_map;

typedef struct s_main
{
	int				width;
	int				height;
	int				player_size;
	float			player_angle;
	double			player_x;
	double			player_y;
	int				step;
	t_map			*map;
	mlx_image_t		*img;
	mlx_texture_t	**texture;
	t_rays			*rays;
	mlx_t			*mlx;
	void			*mlx_win;
	mlx_texture_t	*player_tex[14];
	char			*p_imgs[15];
	int				p_idx;
	int				mouse_use;
	double			fov;
	int				ld;
}	t_main;

typedef struct s_vars
{
	double	xinter;
	double	yinter;
	double	xstep;
	double	ystep;
	double	hor_wall_hit_x;
	double	hor_wall_hit_y;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	next_h_x;
	double	next_h_y;
	double	next_v_x;
	double	next_v_y;
	double	x_to_check;
	double	y_to_check;
	int		found_hor_wall;
	int		found_vert_wall;
	double	hor_hit_distance;
	double	vert_hit_distance;
}	t_vars;

typedef struct s_wall_vars
{
	int		i;
	int		tex_idx;
	double	proj_distance;
	double	correct_distance;
	double	proj_wall_h;
	int		p_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		j;
	double	wall_x;
	double	tex_y;
}	t_wall_vars;

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y);
/*-----------------------parsing--------------------------*/

void		free_map(t_map *map);
void		free_mat(char **map);
char		**ft_get_map_rectangel(char **map);
char		**ft_parse_map(char *file);
char		**ft_parse_map(char *file);
char		**ft_get_map(char *file);
char		**ft_get_map(char *file);
int			ft_check_wall(char **map, int (*fun1)(char c),
				char **(*fun2)(char **map));
int			ft_check_charcters(char **map, char **(*fun2)(char **map));
int			ft_check_doors(char **map);
int			ft_init_map(char *file, t_map *map);
int			ft_check_colors_fc(char **map);
int			ft_check_colors_fc(char **map);
int			ft_check_textures(char **map);
int			get_height(char **map);

/*-----------------------raycasting--------------------------*/

void		ft_raycasting(t_map *map);
void		ft_randering(void *main);
int			ft_has_wall(double x, double y, t_main *main);
void		get_player_pos(t_main *main);
void		mini_map_draw(t_main *main);
void		draw_3d(t_main *main);
void		ft_coloring_c_f(t_main *main);
void		cast_rays(t_main *main);
void		dda(double X0, double Y0, t_main *main);
int			ft_color(int r, int g, int b, int a);
double		ft_distance(double x, double y, t_main *main);
double		ft_adjust_angle(double angle);
void		look_for_v_wall(t_main *main, t_vars *v, int i);
void		init_vars(t_main *main, int i, double angle, t_vars *v);
void		hor_inter(t_main *main, int i, t_vars *v);
void		draw_player(t_main *main, int x, int y);
void		ft_load_player(t_main *main);
void		vert_inter(t_main *main, int i, t_vars *v);
void		ft_look_for_h_wall(t_main *main, t_vars *v, int i);

/*-----------------------mlx_utils--------------------------*/

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		key_hook(void *param);
void		mouse_hook(double xpos, double ypos, void *param);
void		ft_close(void	*param);
void		ft_turn(t_main *main, int redir, double new_x, double new_y);
void		add_player(t_main *main);
void		moves_hook(t_main *main);
void		ft_add_remove_mouse(t_main *main);
#endif
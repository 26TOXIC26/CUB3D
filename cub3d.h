/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/11/30 05:49:31 by ebouboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include "utils/get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// define
# define M_PI 3.14159265358979323846
#define KEY_ESC     65307
#define KEY_W       119
#define KEY_A       97
#define KEY_S       115
#define KEY_D       100
#define KEY_LEFT    65361
#define KEY_RIGHT   65363
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923
# define S_W 1900
# define S_H 1000
# define TILE_SIZE 32
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

# define BLK 0x000000FF
# define GREY 0x808080FF
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFFFFF


#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3


# ifndef BONUS
#  define BONUS 1
# endif

 # define WIN_WIDTH 960 
 # define WIN_HEIGHT 720 
// # define WIN_WIDTH 640
// # define WIN_HEIGHT 480

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.0325
# define ROTSPEED 0.035

# define DIST_EDGE_MOUSE_WRAP 20

/* MINIMAP MACROS */
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

// ERROR MESSAGES
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};


typedef unsigned long	t_ulong;







// structure








// typedef struct s_img
// {
// 	void	*img;
// 	int		*addr;
// 	int		pixel_bits;
// 	int		size_line;
// 	int		endian;
// }	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_mapinfo	mapinfo;
	char		**map;
	char		**xpms;
	char 		**cub_file;
	int colors[2][3];
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
	t_img		minimap;
}	t_data;


int		check_texture(char **map, int *i);
int		check_colors(char **map, int *i);
int	check_map(char **map, int *i);
int		ft_error(char *str);
void take_map (t_data *data, int *i);
void take_colors(t_data *data, int *i);
void take_xpm(t_data *data, int *i);

// utils

int		d2_len(char **str);
void	free_tab(char **str);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
int	ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
char *ft_strdup_max(char *str, int max_len);

#endif


// void free_mlxs(t_data *data);

// typedef struct s_size_map
// {
// 	int	height;
// 	int	width;
// }	t_size_map;

// typedef struct s_img
// {
// 	void	*img;
// 	int		*addr;
// 	int		pixel_bits;
// 	int		size_line;
// 	int		endian;
// }	t_img;

// typedef struct s_texinfo
// {
// 	char			*north;
// 	char			*south;
// 	char			*west;
// 	char			*east;
// 	int				*floor;
// 	int				*ceiling;
// 	unsigned long	hex_floor;
// 	unsigned long	hex_ceiling;
// 	int				size;
// 	int				index;
// 	double			step;
// 	double			pos;
// 	int				x;
// 	int				y;
// }	t_texinfo;

// typedef struct s_data
// {
// 	char **cub_file;
// 	char **xpms;
// 	int colors[2][3];
// 	char **map2d;
// 	int player_x;
// 	int player_y;
// 	double player_angle;
// 	int **textures;
// 	t_texinfo texinfo;
// 	void	*mlx;
// 	void	*win;
// }	t_data;

// typedef struct s_mlx // the mlx structure
// {
// 	t_data	*data;
// 	t_size_map	*size;
// 	int		map_fd;
// 	t_img	*img;
// }		t_mlx;

// function


// // 2d map
// int key_hook(int keycode, t_mlx *mlx);
// void change_moves(char key, t_mlx  *mlx);
// void fill_win(t_mlx *mlx);
// void put_img(t_mlx *mlx, char *path, int x, int y);
// void fill_background(t_mlx *mlx);
// void fill_map(t_mlx *mlx);
// void change_position(t_mlx *mlx);
// // void draw_map(t_mlx *mlx);
// void fill_map(t_mlx *mlx);
// void	cast_rays(t_mlx *mlx);
// void	render_wall(t_mlx *mlx, int ray);
// void	get_angle(t_mlx *mlx);
// int	key_press(int keycode, t_mlx *mlx);
// int   drow_map_pixel(t_mlx *mlx);
// int	execution(t_mlx *mlx);


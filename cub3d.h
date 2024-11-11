/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/11/12 00:11:30 by ebouboul         ###   ########.fr       */
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
// structure

typedef struct mlx_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bytes_per_pixel;
	uint8_t*	pixels;
}	mlx_texture_t;

typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;


typedef struct s_data
{
	char **cub_file;
	char **xpms;
	int colors[2][3];
	char **map2d;
	int player_x;
	int player_y;
	double player_angle;
	char	**ture2d;
	char	**sq_map;
	char	**rgb;
	int		w_map;
	int		h_map;
	char	**ff;
	char	**cc;
}	t_data;

typedef struct s_size_map
{
	int	height;
	int	width;
}	t_size_map;

typedef struct t_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgs;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
	int		m_x;
	int		m_y;
}	t_player;

typedef struct s_ray
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int		flag;
}	t_ray;


typedef struct s_mlx // the mlx structure
{
	t_data	*data;
	t_size_map	*size;
	t_player	*ply;
	t_ray	*ray;
	t_tex	*tex;
	void	*mlx;
	void	*win;
	int		map_fd;
	t_imgs	img;
}		t_mlx;

// function

int		check_texture(char **map, int *i);
int		check_colors(char **map, int *i);
int	check_map(char **map, int *i);
int		ft_error(char *str);
void take_map (t_mlx *mlx, int *i);
void take_colors(t_mlx *mlx, int *i);
void take_xpm(t_mlx *mlx, int *i);
void free_mlxs(t_mlx *mlx);

// 2d map
int key_hook(int keycode, t_mlx *mlx);
void change_moves(char key, t_mlx  *mlx);
void fill_win(t_mlx *mlx);
void put_img(t_mlx *mlx, char *path, int x, int y);
void fill_background(t_mlx *mlx);
void fill_map(t_mlx *mlx);
void change_position(t_mlx *mlx);
// void draw_map(t_mlx *mlx);
void fill_map(t_mlx *mlx);
void	cast_rays(t_mlx *mlx);
void	render_wall(t_mlx *mlx, int ray);
void	get_angle(t_mlx *mlx);
int	key_press(int keycode, t_mlx *mlx);
int   drow_map_pixel(t_mlx *mlx);
int	unit_circle(float angle, char c);
float	nor_angle(float angle);
int	get_rgba(int r, int g, int b, int a);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int	reverse_bytes(int c);


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

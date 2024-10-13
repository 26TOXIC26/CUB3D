/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/13 20:30:43 by ana              ###   ########.fr       */
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
# define S_W 600 // screen width
# define S_H 600 // screen height
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

// structure

typedef struct s_data
{
	char **cub_file;
	char **xpms;
	int colors[2][3];
	char **map2d;
	int player_x;
	int player_y;
	double player_angle;
}	t_data;

typedef struct s_size_map
{
	int	height;
	int	width;
}	t_size_map;

typedef struct s_mlx // the mlx structure
{
	t_data	*data;
	t_size_map	*size;
	void	*mlx;
	void	*win;
	void	*img;
	int		map_fd;
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
void move_player(t_mlx *mlx);
void fill_win(t_mlx *mlx, int color);
void put_img(t_mlx *mlx, char *path, int x, int y);
void fill_background(t_mlx *mlx);
void fill_map(t_mlx *mlx);
void change_position(t_mlx *mlx);


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

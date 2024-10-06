/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/06 16:00:06 by amousaid         ###   ########.fr       */
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
# define S_W 600 // screen width
# define S_H 600 // screen height

// structure

typedef struct s_mlx // the mlx structure
{
	char	**map_x;
	char	**map_y;
	void	*mlx;
	void	*win;
	void	*img;
	int		map_fd;
}		t_mlx;

typedef struct s_size_map
{
	size_t	height;
	size_t	max_len;
}	t_size_map;

// function

int		check_texture(char **map, int *i);
int		check_colors(char **map, int *i);
int	check_map(char **map, int *i);
int		ft_error(char *str);

// utils

int		d2_len(char **str);
void	free_tab(char **str);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif

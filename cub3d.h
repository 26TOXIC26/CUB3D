/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/02 18:02:59 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "utils/get_next_line.h"
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>


// define
# define S_W 600 // screen width
# define S_H 600 // screen height

// structure

typedef struct s_mlx //the mlx structure
{
	void *mlx;
	void *win;
	void *img;
	int map_fd;
	char **map;
} t_mlx;

// function

int		check_texture(char **map, int *i);
int ft_error(char *str);

# endif

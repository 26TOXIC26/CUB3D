/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exrct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 01:43:16 by ebouboul          #+#    #+#             */
/*   Updated: 2024/11/12 00:08:50 by ebouboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"






void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED;
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED;
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}
void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x);
	new_y = roundf(mlx->ply->plyr_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (mlx->data->map2d[map_grid_y][map_grid_x] != '1' && \
	(mlx->data->sq_map[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
	mlx->data->sq_map[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1'))
	{
		mlx->ply->plyr_x = new_x;
		mlx->ply->plyr_y = new_y;
	}
}


void	cub_hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->ply->rot == 1)
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1)
		rotate_player(mlx, 0);
	if (mlx->ply->l_r == 1)
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->l_r == -1)
	{
		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == 1)
	{
		move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == -1)
	{
		move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y);
}

int 	drow_map_pixel(t_mlx *mlx)
{

	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, S_W, S_H);
	cub_hook(mlx, 0, 0);
	cast_rays(mlx);
	// mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx,mlx->win, mlx->img.img, 0, 0);
	return (0);
}














void	get_angle(t_mlx *mlx)
{
	char	c;

	c = mlx->data->map2d[mlx->data->player_x][mlx->data->player_y];
	if (c == 'N')
		mlx->ply->angle = 3 * M_PI / 2;
	if (c == 'S')
		mlx->ply->angle = M_PI / 2;
	if (c == 'E')
		mlx->ply->angle = 0;
	if (c == 'W')
		mlx->ply->angle = M_PI;
	mlx->ply->plyr_x = (mlx->data->player_x * TILE_SIZE) + TILE_SIZE / 2;
	mlx->ply->plyr_y = (mlx->data->player_y * TILE_SIZE) + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * M_PI / 180);
}

int	ft_reles(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_D || keycode == KEY_A)
		mlx->ply->l_r = 0;
	else if (keycode == KEY_S || keycode == KEY_W)
		mlx->ply->u_d = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		mlx->ply->rot = 0;
	return (0);
}
void ft_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx->ply);
	free(mlx->ray);
	// free(mlx->tex);
	// free(mlx->data->map2d);
	// free(mlx->data->sq_map);
	// free(mlx->data->cub_file);
	// free(mlx->data);
	exit(0);
}

// This function is called on key press
int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		ft_exit(mlx);
	else if (keycode == KEY_A)
		mlx->ply->l_r = -1;
	else if (keycode == KEY_D)
		mlx->ply->l_r = 1;
	else if (keycode == KEY_S)
		mlx->ply->u_d = -1;
	else if (keycode == KEY_W)
		mlx->ply->u_d = 1;
	else if (keycode == KEY_LEFT)
		mlx->ply->rot = -1;
	else if (keycode == KEY_RIGHT)
		mlx->ply->rot = 1;
    ft_reles(keycode, mlx);
	return (0);
}

int	execution(t_data *data)
{
	t_mlx	mlx;

	// if (S_H > 1440 || S_W > 2560 || FOV >= 180 || FOV <= 0)
	// 	return (freelist(&data->t), free_map(data), 0);
	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	// mlx.tex = (t_tex *)ft_calloc(sizeof(t_tex), 1);
	mlx.data = data;
	mlx.mlx = mlx_init(S_W, S_H, "cub3D", false);
	if (!mlx.mlx)
		return (ft_exit(&mlx), 0);
	// if (!load_texture(mlx.tex, data->t))
	// 	return (ft_exit(&mlx), 0);
	get_angle(&mlx);
	mlx_key_hook(mlx.mlx, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx, &drow_map_pixel, &mlx);
	mlx_loop(mlx.mlx);
	ft_exit(&mlx);
	return (0);
}

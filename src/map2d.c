/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:16:44 by ebouboul          #+#    #+#             */
/*   Updated: 2024/10/21 13:45:16 by ebouboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void put_img(t_mlx *mlx, char *path, int x, int y)
{
    int		img_width;
    int		img_height;
    void	*img;

    img = mlx_xpm_file_to_image(mlx->mlx, path, &img_width, &img_height);
    // kill the program if the image is not loaded
    if (!img)
    {
        fprintf(stderr, "Error loading image: %s\n", path);
        return;
    }
    mlx_put_image_to_window(mlx->mlx, mlx->win, img, img_width * x, img_height * y);
    mlx_destroy_image(mlx->mlx, img);
}

void fill_win(t_mlx *mlx, int flag)
{
    if (flag == 1)
    {
        fill_background(mlx);
        fill_map(mlx);
    }
    else
        change_position(mlx);
}

void fill_background(t_mlx *mlx)
{
    int i;
    int j;

    i = 0;
    while(i < mlx->size->height)
    {
        mlx->data->map2d[i] = ft_strdup_max(mlx->data->map2d[i], mlx->size->width);
        i++;
    }
    i = 0;
    while (i < mlx->size->height)
    {
        j = 0;
        while (j < mlx->size->width)
        {
            put_img(mlx, "img/wall.xpm", j, i);
            j++;
        }
        i++;
    }
}

void fill_map(t_mlx *mlx)
{
    int i;
    int j;

    i = 0;
    while (mlx->data->map2d[i])
    {
        j = 0;
        while (mlx->data->map2d[i][j])
        {
            if (mlx->data->map2d[i][j] == '0')
                put_img(mlx, "img/square.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'N')
                put_img(mlx, "img/north.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'S')
                put_img(mlx, "img/south.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'E')
                put_img(mlx, "img/east.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'W')
                put_img(mlx, "img/west.xpm", j , i );
            j++;
        }
        i++;
    }
}

void change_position(t_mlx *mlx)
{
    int i;
    int j;

    i = 0;
    while (i < mlx->size->height)
    {
        j = 0;
        while (j < mlx->size->width)
        {
            if (mlx->data->map2d[i][j] == 'N')
                put_img(mlx, "img/north.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'S')
                put_img(mlx, "img/south.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'E')
                put_img(mlx, "img/east.xpm", j , i );
            else if (mlx->data->map2d[i][j] == 'W')
                put_img(mlx, "img/west.xpm", j , i );
            else if (mlx->data->map2d[i][j] == '0')
                put_img(mlx, "img/square.xpm", j , i );
            j++;
        }
        i++;
    }
}

void change_moves(char key, t_mlx  *mlx)
{
    char c;

    if (key == 'w')
    {
        if (mlx->data->map2d[mlx->data->player_y - 1][mlx->data->player_x] == '0')
        {
            c = mlx->data->map2d[mlx->data->player_y][mlx->data->player_x];
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = '0';
            mlx->data->player_y--;
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = c;
        }
    }
    else if (key == 's')
    {
        if (mlx->data->map2d[mlx->data->player_y + 1][mlx->data->player_x] == '0')
        {
            c = mlx->data->map2d[mlx->data->player_y][mlx->data->player_x];
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = '0';
            mlx->data->player_y++;
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = c;
        }
    }
    else if (key == 'a')
    {
        if (mlx->data->map2d[mlx->data->player_y][mlx->data->player_x - 1] == '0')
        {
            c = mlx->data->map2d[mlx->data->player_y][mlx->data->player_x];
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = '0';
            mlx->data->player_x--;
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = c;
        }
    }
    else if (key == 'd')
    {
        if (mlx->data->map2d[mlx->data->player_y][mlx->data->player_x + 1] == '0')
        {
            c = mlx->data->map2d[mlx->data->player_y][mlx->data->player_x];
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = '0';
            mlx->data->player_x++;
            mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = c;
        }
    }
    move_player(mlx);
}

void move_player(t_mlx *mlx)
{
    fill_win(mlx, 0);
    // fill_win(mlx, 1);
}

void rotate_player_image(t_mlx *mlx)
{
    int center_x;
    int center_y;
    double angle;

    center_x = mlx->data->player_x;
    center_y = mlx->data->player_y;
    angle = mlx->data->player_angle;
    if (angle >= 0 && angle < (M_PI / 2))
        mlx->data->map2d[center_y][center_x] = 'E';
    else if (angle >= (M_PI / 2) && angle < M_PI)
        mlx->data->map2d[center_y][center_x] = 'S';
    else if (angle >= M_PI && angle < 3 * (M_PI / 2))
        mlx->data->map2d[center_y][center_x] = 'W';
    else
        mlx->data->map2d[center_y][center_x] = 'N';
    move_player(mlx);
}

void change_view(t_mlx *mlx, int keycode)
{
    if (keycode == LEFT_KEY)
    {
        mlx->data->player_angle -= M_PI / 2;
        if (mlx->data->player_angle < 0)
            mlx->data->player_angle += 2 * M_PI;
    }
    else if (keycode == RIGHT_KEY)
    {
        mlx->data->player_angle += M_PI / 2;
        if (mlx->data->player_angle >= 2 * M_PI)
            mlx->data->player_angle -= 2 * M_PI;
    }
    rotate_player_image(mlx);
}

void key_hook(int keycode, t_mlx *mlx)
{
    if (keycode == ESC_KEY)
    {
        printf("ESC key pressed\n");
        free_mlxs(mlx);
        exit(0);
    }
    else if (keycode == W_KEY)
    {
        printf("W key pressed\n");
        change_moves('w', mlx);
    }
    else if (keycode == S_KEY)
    {
        printf("S key pressed\n");
        change_moves('s', mlx);
    }
    else if (keycode == A_KEY)
    {
        printf("A key pressed\n");
        change_moves('a', mlx);
    }
    else if (keycode == D_KEY)
    {
        printf("D key pressed\n");
        change_moves('d', mlx);
    }
    else if (keycode == LEFT_KEY)
    {
        printf("LEFT key pressed\n");
        change_view(mlx, keycode);
    }
    else if (keycode == RIGHT_KEY)
    {
        printf("RIGHT key pressed\n");
        change_view(mlx, keycode);
    }
}

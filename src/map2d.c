#include "../cub3d.h"
#include <math.h>

// #define RAY_LENGTH 300000
// #define NUM_RAYS 100
// #define TILE_SIZE 40
// #define FOV_ANGLE (60 * M_PI / 180)

// Draw a line using Bresenham's algorithm
void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;
    if (x0 < x1)
        sx = 1;
    else
        sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;
    int err = dx - dy;
    int e2;
    
    while (1)
    {
        mlx_pixel_put(mlx->mlx, mlx->win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// Draw a single tile
void draw_tile(t_mlx *mlx, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mlx_pixel_put(mlx->mlx, mlx->win, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

// Check if a point intersects with a wall
int is_wall(t_mlx *mlx, double x, double y)
{
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);
    if (map_x < 0 || map_x >= mlx->size->width || 
        map_y < 0 || map_y >= mlx->size->height)
        return (1); // Treat out-of-bounds as a wall
    return (mlx->data->map2d[map_y][map_x] == '1');
}


// Cast a single ray and return the hit point
void cast_ray(t_mlx *mlx, double angle, double *hit_x, double *hit_y)
{
    double sin_a = sin(angle);
    double cos_a = cos(angle);
    double cur_x = mlx->data->player_x * TILE_SIZE + TILE_SIZE / 2;
    double cur_y = mlx->data->player_y * TILE_SIZE + TILE_SIZE / 2;
    double step = 1.0;

    while (sqrt(pow(cur_x - (mlx->data->player_x * TILE_SIZE + TILE_SIZE / 2), 2) +
               pow(cur_y - (mlx->data->player_y * TILE_SIZE + TILE_SIZE / 2), 2)) < RAY_LENGTH)
    {
        if (is_wall(mlx, cur_x, cur_y))
        {
            *hit_x = cur_x;
            *hit_y = cur_y;
            return;
        }
        cur_x += cos_a * step;
        cur_y += sin_a * step;
    }
    *hit_x = cur_x;
    *hit_y = cur_y;
}

// Draw the map with raycasting
void fill_map(t_mlx *mlx)
{
    int i = 0;
    int j;

    // Draw the map grid
    while (mlx->data->map2d[i])
    {
        j = 0;
        while (mlx->data->map2d[i][j])
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            if (mlx->data->map2d[i][j] == '1')
                draw_tile(mlx, x, y, 0xFFFFFF); // White for walls
            else if (mlx->data->map2d[i][j] == '0')
                draw_tile(mlx, x, y, 0x000000); // Black for empty space
            j++;
        }
        i++;
    }

    // Draw player
    int player_x = mlx->data->player_x * TILE_SIZE + TILE_SIZE / 2;
    int player_y = mlx->data->player_y * TILE_SIZE + TILE_SIZE / 2;
    i = -3;
    while (i <= 3)
    {
        j = -3;
        while (j <= 3)
        {
            mlx_pixel_put(mlx->mlx, mlx->win, player_x + i, player_y + j, 0xFF0000);
            j++;
        }
        i++;
    }

    // Cast rays
    double ray_angle = mlx->data->player_angle - FOV_ANGLE / 2;
    double angle_step = FOV_ANGLE / NUM_RAYS;

    i = 0;
    while (i < NUM_RAYS)
    {
        double hit_x, hit_y;
        cast_ray(mlx, ray_angle, &hit_x, &hit_y);
        draw_line(mlx, player_x, player_y, hit_x, hit_y, 0x00FF00); // Green rays
        ray_angle += angle_step;
        i++;
    }

    // Draw direction indicator
    double dir_x = player_x + cos(mlx->data->player_angle) * 20;
    double dir_y = player_y + sin(mlx->data->player_angle) * 20;
    draw_line(mlx, player_x, player_y, dir_x, dir_y, 0xFF0000); // Red direction line
}

// 
void update_map(t_mlx *mlx)
{
    int i = 0;
    int j;

    while (mlx->data->map2d[i])
    {
        j = 0;
        while (mlx->data->map2d[i][j])
        {
            if (mlx->data->map2d[i][j] == 'E')
                mlx->data->map2d[i][j] = '0';
            j++;
        }
        i++;
    }
    mlx->data->map2d[(int)mlx->data->player_y][(int)mlx->data->player_x] = 'E';
}
void change_moves(char key, t_mlx *mlx)
{
    double new_x = mlx->data->player_x;
    double new_y = mlx->data->player_y;
    double move_step = 0.1;
    double move_x = cos(mlx->data->player_angle * M_PI / 180.0) * move_step;
    double move_y = sin(mlx->data->player_angle * M_PI / 180.0) * move_step;

    if (key == 'w')
    {
        new_x += move_x;
        new_y += move_y;
    }
    else if (key == 's')
    {
        new_x -= move_x;
        new_y -= move_y;
    }
    else if (key == 'a')
    {
        new_x += move_y;
        new_y -= move_x;
    }
    else if (key == 'd')
    {
        new_x -= move_y;
        new_y += move_x;
    }

    // printf("New coordinates (%.2f, %.2f) checking map at [%d][%d]: %c\n", 
    //        new_x, new_y, (int)new_y, (int)new_x, mlx->data->map2d[(int)new_y][(int)new_x]);

    if (mlx->data->map2d[(int)new_y][(int)new_x] != '1')
    {
        mlx->data->player_x = new_x;
        mlx->data->player_y = new_y;
    }

    update_map(mlx);
    fill_map(mlx);
}


// void change_moves(char key, t_mlx *mlx)
// {
//     double new_x = mlx->data->player_x;
//     double new_y = mlx->data->player_y;
//     double move_step = 0.1; // smaller step for smoother movement
//     double move_x = cos(mlx->data->player_angle * M_PI / 180) * move_step;
//     double move_y = sin(mlx->data->player_angle * M_PI / 180) * move_step;

//     // printf("move_x: %f, move_y: %f\n", move_x, move_y); 
//     if (key == 'w')
//     {
//         new_x += move_x;
//         new_y += move_y;
//     }
//     else if (key == 's')
//     {
//         new_x -= move_x;
//         new_y -= move_y;
//     }
//     else if (key == 'a')
//     {
//         new_x += move_y;
//         new_y -= move_x;
//     }
//     else if (key == 'd')
//     {
//         new_x -= move_y;
//         new_y += move_x;
//     }
//     // printf("New player position: %f, %f\n", new_x, new_y);
//     printf("Trying to move to (%.2f, %.2f) -> Map at [%d][%d]: %c\n", 
//         new_x, new_y, (int)new_y, (int)new_x, mlx->data->map2d[(int)new_y][(int)new_x]);


//     // Wall collision check (cast to int to map coordinates)
//     if (mlx->data->map2d[(int)new_y][(int)new_x] != '1')
//     {
//         mlx->data->player_x = (int)new_x;
//         mlx->data->player_y = (int)new_y;
//     }
//     update_map(mlx);  // Ensure this function properly redraws based on new coordinates
//     fill_map(mlx);    // Redraw map with updated player position
// }



// Handle key events
// int key_hook(int keycode, t_mlx *mlx)
// {
//     // printf("Key pressed: %d\n", keycode);
//     if (keycode == ESC_KEY)
//     {
//         free_mlxs(mlx);
//         exit(0);
//     }
//     else if (keycode == W_KEY)
//         change_moves('w', mlx);
//     else if (keycode == S_KEY)
//         change_moves('s', mlx);
//     else if (keycode == A_KEY)
//         change_moves('a', mlx);
//     else if (keycode == D_KEY)
//         change_moves('d', mlx);
//     else if (keycode == LEFT_KEY)
//     {
//         mlx->data->player_angle -= 0.1;
//         fill_map(mlx);
//     }
//     else if (keycode == RIGHT_KEY)
//     {
//         mlx->data->player_angle += 0.1;
//         fill_map(mlx);
//     }
//     return (0);
// }
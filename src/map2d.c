#include "../cub3d.h"
#include <math.h>
#include <stdio.h>
#include "mlx.h"
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TILE_SIZE 40  // Size of each tile in pixels
#define MAX_DEPTH 1000 // Maximum depth the ray can travel
#define FOV (M_PI / 3) // Field of View
#define NUM_RAYS 300   // Number of rays to cast per frame

int is_wall(t_mlx *mlx, int x, int y) {
    if (x < 0 || y < 0 || x >= mlx->size->width || y >= mlx->size->height)
        return 1; // Out of bounds is considered a wall
    return mlx->data->map2d[y][x] == '1'; // Wall is represented by '1'
}
// Cast a ray from the player's position and return the distance to the wall
double cast_ray(t_mlx *mlx, double angle) {
    double ray_x = mlx->data->player_x * TILE_SIZE + TILE_SIZE / 2;
    double ray_y = mlx->data->player_y * TILE_SIZE + TILE_SIZE / 2;
    double ray_angle = angle;

    // Direction of ray
    double ray_dx = cos(ray_angle);
    double ray_dy = sin(ray_angle);

    double depth = 0;
    double dist_to_wall = 0;
    int hit = 0;

    // Trace the ray across the map
    while (depth < MAX_DEPTH && !hit) {
        ray_x += ray_dx * TILE_SIZE; // Move by tile size
        ray_y += ray_dy * TILE_SIZE; // Move by tile size
        depth += TILE_SIZE;

        // Check if the ray hits a wall
        if (is_wall(mlx, (int)(ray_x / TILE_SIZE), (int)(ray_y / TILE_SIZE))) {
            hit = 1;
            dist_to_wall = depth;
        }
    }
    return dist_to_wall;
}

// Wall collision checking function

// Draw a vertical line to represent a ray hit
void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

// Render rays based on player position and angle
void render_rays(t_mlx *mlx) {
    double start_angle = mlx->data->player_angle - (FOV / 2); // Field of View
    double angle_step = FOV / NUM_RAYS; // Step between each ray

    int ray = 0;
    while (ray < NUM_RAYS) {
        double angle = start_angle + ray * angle_step;
        double dist_to_wall = cast_ray(mlx, angle); // Cast ray and get distance

        // Render the wall (as a vertical line)
        int wall_height = (int)(WIN_HEIGHT / dist_to_wall); // Calculate wall height based on distance
        int wall_top = (WIN_HEIGHT - wall_height) / 2;
        int wall_bottom = wall_top + wall_height;

        // Draw the vertical line (this simulates the wall)
        draw_line(mlx->mlx, mlx->win, ray, wall_top, ray, wall_bottom, 0x00FF00); // Green for walls

        ray++;
    }
}

// Draws a filled square tile for each map cell
void draw_tile(void *mlx_ptr, void *win_ptr, int x, int y, int color) {
    int i = 0;
    while (i < TILE_SIZE) {
        int j = 0;
        while (j < TILE_SIZE) {
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

// Fill the window with the background and map
void fill_background(t_mlx *mlx) {
    int i, j;

    i = 0;
    while (i < mlx->size->height) {
        j = 0;
        while (j < mlx->size->width) {
            printf("i: %d, j: %d\n", i, j);
            draw_tile(mlx->mlx, mlx->win, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF); // White for empty space
            j++;
        }
        i++;
    }
}

// Fill the map (draw map tiles and player)
void fill_map(t_mlx *mlx) {
    int i = 0;
    while (mlx->data->map2d[i]) {
        int j = 0;
        while (mlx->data->map2d[i][j]) {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            if (mlx->data->map2d[i][j] == '0') {
                draw_tile(mlx->mlx, mlx->win, x, y, 0x000000); // Black for walls
            } else if (mlx->data->map2d[i][j] == '1') {
                draw_tile(mlx->mlx, mlx->win, x, y, 0xFFFFFF); // White for empty space
            }
            j++;
        }
        i++;
    }
}

// Change the player position on the map
void change_position(t_mlx *mlx) {
    int i = 0;
    while (mlx->data->map2d[i]) {
        int j = 0;
        while (mlx->data->map2d[i][j]) {
            if (mlx->data->map2d[i][j] == 'N' || mlx->data->map2d[i][j] == 'S' || mlx->data->map2d[i][j] == 'E' || mlx->data->map2d[i][j] == 'W') {
                mlx->data->player_x = j;
                mlx->data->player_y = i;
                return ;
            }
            j++;
        }
        i++;
    }
}

// Fill the window with the map and render rays
void fill_win(t_mlx *mlx, int flag) {
    if (flag == 1) {
        fill_background(mlx); // Fill background (can be white or some color)
        fill_map(mlx);         // Fill the map
        render_rays(mlx);      // Render the rays
    } else {
        change_position(mlx);  // Handle player movement and redraw
    }
}

// Change the player position on the map
void move_player_to(t_mlx *mlx, int new_x, int new_y) {
    char c = mlx->data->map2d[mlx->data->player_y][mlx->data->player_x];
    mlx->data->map2d[mlx->data->player_y][mlx->data->player_x] = '0';
    mlx->data->player_x = new_x;
    mlx->data->player_y = new_y;
    mlx->data->map2d[new_y][new_x] = c;
}

// Handle player movement based on key presses
void change_moves(char key, t_mlx *mlx) {
    if (key == 'w' && mlx->data->map2d[mlx->data->player_y - 1][mlx->data->player_x] == '0')
        move_player_to(mlx, mlx->data->player_x, mlx->data->player_y - 1);
    else if (key == 's' && mlx->data->map2d[mlx->data->player_y + 1][mlx->data->player_x] == '0')
        move_player_to(mlx, mlx->data->player_x, mlx->data->player_y + 1);
    else if (key == 'a' && mlx->data->map2d[mlx->data->player_y][mlx->data->player_x - 1] == '0')
        move_player_to(mlx, mlx->data->player_x - 1, mlx->data->player_y);
    else if (key == 'd' && mlx->data->map2d[mlx->data->player_y][mlx->data->player_x + 1] == '0')
        move_player_to(mlx, mlx->data->player_x + 1, mlx->data->player_y);
    move_player(mlx);
}

// Redraw the window after player moves
void move_player(t_mlx *mlx) {
    fill_win(mlx, 0);
}

// Normalize the angle to be between 0 and 2 * PI
void normalize_angle(double *angle) {
    *angle = fmod(*angle, 2 * M_PI);
    if (*angle < 0)
        *angle += 2 * M_PI;
}

// Rotate the player based on input
void rotate_player_image(t_mlx *mlx) {
    int center_x = mlx->data->player_x;
    int center_y = mlx->data->player_y;
    double angle = mlx->data->player_angle;

    if (angle >= 0 && angle < (M_PI / 2))
        mlx->data->map2d[center_y][center_x] = 'E';
    else if (angle >= (M_PI / 2) && angle < M_PI)
        mlx->data->map2d[center_y][center_x] = 'S';
    else if (angle >= M_PI && angle < 3 * (M_PI / 2))
        mlx->data->map2d[center_y][center_x] = 'W';
    else
        mlx->data->map2d[center_y][center_x] = 'N';
}

void change_view(t_mlx *mlx, int keycode) {
    double angle = mlx->data->player_angle;
    if (keycode == LEFT_KEY)
        angle -= 0.1;
    else if (keycode == RIGHT_KEY)
        angle += 0.1;
    normalize_angle(&angle);
    mlx->data->player_angle = angle;
    rotate_player_image(mlx);
    fill_win(mlx, 0);
}

// Handle key events
int key_hook(int keycode, t_mlx *mlx) {
    if (keycode == ESC_KEY) {
        printf("ESC key pressed\n");
        free_mlxs(mlx);
        exit(0);
    } else if (keycode == W_KEY)
        change_moves('w', mlx);
    else if (keycode == S_KEY)
        change_moves('s', mlx);
    else if (keycode == A_KEY)
        change_moves('a', mlx);
    else if (keycode == D_KEY)
        change_moves('d', mlx);
    else if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
        change_view(mlx, keycode);

    return (0);
}

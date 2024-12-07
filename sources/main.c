/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:18:26 by amousaid          #+#    #+#             */
/*   Updated: 2024/12/07 13:57:21 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_controls(void)
{
	printf(CYAN "\n");
	printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("░░█░█░█▀▀░█░░░█▀▀░█▀█░█▄█░█▀▀░\n");
	printf("░░█▄█░█▀▀░█░░░█░░░█░█░█░█░█▀▀░\n");
	printf("░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░\n");
	printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("░▀█▀░█▀█░░█▀▀░█░█░█▀▄░▀▀█░█▀▄░\n");
	printf("░░█░░█░█░░█░░░█░█░█▀▄░▀▀█░█░█░\n");
	printf("░░▀░░▀▀▀░░▀▀▀░▀▀▀░▀▀░░▀▀▀░▀▀░░\n");
	printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf(RESET "\n");
	printf(CYAN "Controls:\n" RESET);
	printf(CYAN "\tW" RESET ": Move forward\t\t");
	printf(CYAN "S" RESET ": Move backward\n");
	printf(CYAN "\tA" RESET ": Strafe left\t\t");
	printf(CYAN "D" RESET ": Strafe right\n");
	printf(CYAN "\t<" RESET ": Rotate left\t\t");
	printf(CYAN ">" RESET ": Rotate right\n");
	if (BONUS)
		printf(CYAN "\tMouse" RESET ": Rotate view\n");
	printf(CYAN "\tESC" RESET ": Exit game\n");
	printf("\n");
}

static int	parse_args(t_data *data, char **av)
{
	if (check_file(av[1], true) == FAILURE)
		clean_exit(data, FAILURE);
	parse_data(av[1], data);
	if (get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	if (DEBUG_MSG)
		debug_display_data(data);
	return (0);
}

void	print_all(t_data *data)
{
	printf("mlx: %p\n", data->mlx);
	printf("win: %p\n", data->win);
	printf("win_height: %d\n", data->win_height);
	printf("win_width: %d\n", data->win_width);
	printf("mapinfo.fd: %d\n", data->mapinfo.fd);
	printf("mapinfo.line_count: %d\n", data->mapinfo.line_count);
	printf("mapinfo.path: %s\n", data->mapinfo.path);
	printf("mapinfo.height: %d\n", data->mapinfo.height);
	printf("mapinfo.width: %d\n", data->mapinfo.width);
	printf("mapinfo.index_end_of_map: %d\n", data->mapinfo.index_end_of_map);
	printf("map: %p\n", data->map);
	printf("player.dir: %c\n", data->player.dir);
	printf("player.pos_x: %f\n", data->player.pos_x);
	printf("player.pos_y: %f\n", data->player.pos_y);
	printf("ray.camera_x: %f\n", data->ray.camera_x);
	printf("ray.dir_x: %f\n", data->ray.dir_x);
	printf("ray.dir_y: %f\n", data->ray.dir_y);
	printf("ray.map_x: %d\n", data->ray.map_x);
	printf("ray.map_y: %d\n", data->ray.map_y);
	printf("ray.step_x: %d\n", data->ray.step_x);
	printf("ray.step_y: %d\n", data->ray.step_y);
	printf("ray.sidedist_x: %f\n", data->ray.sidedist_x);
	printf("ray.sidedist_y: %f\n", data->ray.sidedist_y);
	printf("ray.deltadist_x: %f\n", data->ray.deltadist_x);
	printf("ray.deltadist_y: %f\n", data->ray.deltadist_y);
	printf("ray.wall_dist: %f\n", data->ray.wall_dist);
	printf("ray.wall_x: %f\n", data->ray.wall_x);
	printf("ray.side: %d\n", data->ray.side);
	printf("ray.line_height: %d\n", data->ray.line_height);
	printf("ray.draw_start: %d\n", data->ray.draw_start);
	printf("ray.draw_end: %d\n", data->ray.draw_end);
	printf("texture_pixels: %p\n", data->texture_pixels);
	printf("textures: %p\n", data->textures);
	printf("texinfo.index: %d\n", data->texinfo.index);
	printf("texinfo.size: %d\n", data->texinfo.size);
	printf("texinfo.x: %d\n", data->texinfo.x);
	printf("texinfo.y: %d\n", data->texinfo.y);
	printf("texinfo.step: %f\n", data->texinfo.step);
	printf("texinfo.pos: %f\n", data->texinfo.pos);
	printf("texinfo.hex_ceiling: %lu\n", data->texinfo.hex_ceiling);
	printf("texinfo.hex_floor: %lu\n", data->texinfo.hex_floor);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	init_mlx(&data);
	init_textures(&data);
	print_controls();
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}

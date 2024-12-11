/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:18:26 by amousaid          #+#    #+#             */
/*   Updated: 2024/12/11 18:25:13 by ebouboul         ###   ########.fr       */
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

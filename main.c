/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:17:43 by amousaid          #+#    #+#             */
/*   Updated: 2024/12/02 07:39:46 by ebouboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_syntax(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (ft_strcmp(&str[i - 4], ".cub"))
		return (ft_error("Error:  Invalid file extension"));
	return (0);
}

t_mapinfo	sizeof_map(int fd)
{
	t_mapinfo	size;
	char	*line;

	size.height = 0;
	line = get_next_line(fd);
	size.width = ft_strlen(line);
	while (line)
	{
		size.height++;
		free(line);
		line = get_next_line(fd);
		if (line && ft_strlen(line) > size.width)
			size.width = ft_strlen(line);
	}
	free(line);
	return (size);
}

int	ft_check_map(t_data *data)
{
	int	i;

	i = 0;
	if (!check_texture(data->cub_file, &i) || !check_colors(data->cub_file, &i) || !check_map(data->cub_file, &i))
		return (0);
	return (1);
}

char *ft_strdup_max(char *str, int width)
{
	char	*new;
	int		i;

	new = malloc(width + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (i < width)
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**init_map(t_data *data, char *av)
{
	char	**map2d;
	t_mapinfo	size;
	char 	*line;
	int		i;

	data->mapinfo.fd = open(av, O_RDONLY);
	size = sizeof_map(data->mapinfo.fd);
	close(data->mapinfo.fd);
	data->mapinfo.fd = open(av, O_RDONLY);
	map2d = malloc(sizeof(char *) * (size.height + 1));
	if (!map2d)
		return (NULL);
	i = 0;
	line = get_next_line(data->mapinfo.fd);
	while (line)
	{
		map2d[i] = ft_strdup_max(line, size.width);
		free(line);
		line = get_next_line(data->mapinfo.fd);
		i++;
	}
	map2d[i] = NULL;
	close(data->mapinfo.fd);
	return (map2d);
}

void	init_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->player.pos_x = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player.pos_x = j;
				data->player.pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	split_c_file(t_data *data)
{
	int i;

	i = 0;
	take_xpm(data, &i);
	take_colors(data, &i);
	while (data->cub_file[i] && data->cub_file[i][0] == '\n')
		i++;
	take_map(data, &i);
	i = 0;
	data->mapinfo.height = d2_len(data->map);
	data->mapinfo.width = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) > data->mapinfo.width)
			data->mapinfo.width = ft_strlen(data->map[i]);
		i++;
	}
}

void	ft_init(t_data *data, char *av)
{
	data->cub_file = init_map(data, av);
	if (!ft_check_map(data))
	{
		free_tab(data->cub_file);
		exit(1);
	}
	split_c_file(data);
	init_position(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_error("Error:  Invalid number of arguments"));
	init_data(&data);
	if (!ft_syntax(av[1]))
		ft_init(&data, av[1]);

	init_mlx(&data);
	init_textures(&data);
	// print_controls();
	render_images(&data);
	listen_for_input(&data);
	// mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);

	// execution(&data);
	// free_mlxs(&mlx);
	return (0);
}

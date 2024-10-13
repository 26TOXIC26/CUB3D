/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:17:43 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/13 19:52:46 by ana              ###   ########.fr       */
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

t_size_map	sizeof_map(int fd)
{
	t_size_map	size;
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

int	ft_check_map(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (!check_texture(mlx->data->cub_file, &i) || !check_colors(mlx->data->cub_file, &i) || !check_map(mlx->data->cub_file, &i))
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

char	**init_map(t_mlx *mlx, char *av)
{
	char	**map2d;
	t_size_map	size;
	char 	*line;
	int		i;

	mlx->map_fd = open(av, O_RDONLY);
	if (mlx->map_fd < 0)
	{
		ft_error("Error:  Invalid file");
		exit(1);
	}
	size = sizeof_map(mlx->map_fd);
	close(mlx->map_fd);
	mlx->map_fd = open(av, O_RDONLY);
	map2d = malloc(sizeof(char *) * (size.height + 1));
	if (!map2d)
		return (NULL);
	i = 0;
	line = get_next_line(mlx->map_fd);
	while (line)
	{
		map2d[i] = ft_strdup_max(line, size.width);
		free(line);
		line = get_next_line(mlx->map_fd);
		i++;
	}
	map2d[i] = NULL;
	close(mlx->map_fd);
	return (map2d);
}

void	init_position(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->data->player_angle = 0.0;
	while (mlx->data->map2d[i])
	{
		j = 0;
		while (mlx->data->map2d[i][j])
		{
			if (mlx->data->map2d[i][j] == 'N' || mlx->data->map2d[i][j] == 'S' || mlx->data->map2d[i][j] == 'E' || mlx->data->map2d[i][j] == 'W')
			{
				mlx->data->player_x = j;
				mlx->data->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	split_c_file(t_mlx *mlx)
{
	int i;

	i = 0;
	take_xpm(mlx, &i);
	take_colors(mlx, &i);
	while (mlx->data->cub_file[i] && mlx->data->cub_file[i][0] == '\n')
		i++;
	take_map(mlx, &i);
	i = 0;
	mlx->size->height = d2_len(mlx->data->map2d);
	mlx->size->width = ft_strlen(mlx->data->map2d[i]);
	while (mlx->data->map2d[i])
	{
		if (ft_strlen(mlx->data->map2d[i]) > mlx->size->width)
			mlx->size->width = ft_strlen(mlx->data->map2d[i]);
		i++;
	}
}

void	ft_init(t_mlx *mlx, char *av)
{
	mlx->data = malloc(sizeof(t_data));
	mlx->size = malloc(sizeof(t_size_map));
	if (!mlx->data)
	{
		ft_error("Error:  Memory allocation failed");
		exit(1);
	}
	mlx->data->cub_file = init_map(mlx, av);
	if (!mlx->data->cub_file)
	{
		ft_error("Error:  Memory allocation failed");
		exit(1);
	}
	if (!ft_check_map(mlx))
	{
		free_tab(mlx->data->cub_file);
		exit(1);
	}
	split_c_file(mlx);
	init_position(mlx);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->size->width * 54, mlx->size->height * 54, "Cub3D");
	// mlx->img = mlx_new_image(mlx->mlx, S_W, S_H);
	// mlx->img = mlx_xpm_file_to_image(mlx->mlx, mlx->data->xpms[0], (int )0);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	fill_win(mlx, 1);
	mlx_hook(mlx->win, 2, 1L << 0, key_hook, mlx);


	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (ft_error("Error:  Invalid number of arguments"));
	if (!ft_syntax(av[1]))
		ft_init(&mlx, av[1]);
	return (0);
}

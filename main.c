/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:17:43 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/03 16:28:52 by amousaid         ###   ########.fr       */
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

int	sizeof_map(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (i);
}

int	ft_check_map(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (!check_texture(mlx->map, &i) || !check_colors(mlx->map, &i))
		return (0);
	return (1);
}

char	**init_map(t_mlx *mlx, char *av)
{
	char	**map;
	int		i;

	mlx->map_fd = open(av, O_RDONLY);
	if (mlx->map_fd < 0)
	{
		ft_error("Error:  Invalid file");
		exit(1);
	}
	i = sizeof_map(mlx->map_fd);
	close(mlx->map_fd);
	mlx->map_fd = open(av, O_RDONLY);
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (NULL);
	i = 0;
	map[i] = get_next_line(mlx->map_fd);
	while (map[i])
	{
		i++;
		map[i] = get_next_line(mlx->map_fd);
	}
	map[i] = NULL;
	close(mlx->map_fd);
	return (map);
}

void	ft_init(t_mlx *mlx, char *av)
{
	mlx->map = init_map(mlx, av);
	if (!ft_check_map(mlx))
	{
		free_tab(mlx->map);
		exit(1);
	}
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, S_W, S_H, "cub3d");
	mlx->img = mlx_new_image(mlx->mlx, S_W, S_H);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
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

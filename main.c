/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:17:43 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/06 17:17:34 by amousaid         ###   ########.fr       */
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
	size.max_len = ft_strlen(line);
	while (line)
	{
		size.height++;
		free(line);
		line = get_next_line(fd);
		if (line && ft_strlen(line) > size.max_len)
			size.max_len = ft_strlen(line);
	}
	free(line);
	return (size);
}

int	ft_check_map(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (!check_texture(mlx->map_x, &i) || !check_colors(mlx->map_x, &i) || !check_map(mlx->map_x, &i))
		return (0);
	return (1);
}

char *ft_strdup_max(char *str, int max_len)
{
	char	*new;
	int		i;

	new = malloc(max_len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (i < max_len)
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**init_map_x(t_mlx *mlx, char *av)
{
	char	**map_x;
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
	map_x = malloc(sizeof(char *) * (size.height + 1));
	if (!map_x)
		return (NULL);
	i = 0;
	line = get_next_line(mlx->map_fd);
	while (line)
	{
		map_x[i] = ft_strdup_max(line, size.max_len);
		free(line);
		line = get_next_line(mlx->map_fd);
		i++;
	}
	map_x[i] = NULL;
	close(mlx->map_fd);
	return (map_x);
}

void	ft_init(t_mlx *mlx, char *av)
{
	mlx->map_x = init_map_x(mlx, av);
	// mlx->map_y = init_map_y(mlx);
	if (!ft_check_map(mlx))
	{
		free_tab(mlx->map_x);
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

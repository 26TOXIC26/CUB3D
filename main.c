/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:17:43 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/02 19:32:24 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	free_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int ft_syntax(char *str)
{
	int i;

	i = ft_strlen(str);
	if (ft_strcmp(&str[i - 4], ".cub"))
		return (ft_error("Error:  Invalid file extension"));
	return (0);
}

int sizeof_map(int fd)
{
	int i;
	char *line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	return (i);
}


int ft_check_map(t_mlx *mlx)
{
	int i;

	i = 0;
	if (!check_texture(mlx->map, &i))
		return (0);
	return (1);
}

char **init_map(int fd, char *av)
{
	char **map;
	int i;

	i = sizeof_map(fd);
	close(fd);
	fd = open(av, O_RDONLY);
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (NULL);
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i])
	{
		i++;
		map[i] = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void ft_init(t_mlx *mlx, char *av)
{
	mlx->map_fd = open(av, O_RDONLY);
	mlx->map = init_map(mlx->map_fd, av);
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

int main(int ac, char **av)
{
	t_mlx mlx;

	if (ac != 2)
		return (ft_error("Error:  Invalid number of arguments"));
	if (!ft_syntax(av[1]))
		ft_init(&mlx, av[1]);
	return (0);
}
